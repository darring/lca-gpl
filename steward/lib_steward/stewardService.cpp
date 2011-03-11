/*
 stewardService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the gSOAP interfaces
 */

#include <strings.h>

// Nasty gSOAP bindings
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "wsaapi.h"

#include "logger.h"
#include "stewardService.h"
#include "EIL_defines.h"
#include "uniqueHash.h"
#include "CCMS_commands.h"

StewardService::StewardService(StewardLogger *myLogger)
{
    logger = myLogger;
    logger->QuickLog("StewardService> Initializing the steward service");

    // TODO Initialization here
    currentState = STATE_None;
    soap_init(&soap);
    soap_register_plugin(&soap, soap_wsa);

    logger->QuickLog("StewardService> Service initialized...");
}

StewardService::~StewardService()
{
    soap_destroy(&soap); // remove deserialized class instances (C++ only)
    soap_end(&soap); // clean up and remove deserialized data
    soap_done(&soap); // detach environment (last use and no longer in scope)
}

CCMS_Command StewardService::QueryForClientCommands(
            char *hostname,
            char *hwaddr,
            char *order_num,
            MachineType mType)
{
    // We default to command error, and assume that if we never change it
    // something went wrong.
    CCMS_Command returnCommand;
    returnCommand.ReturnState = COMMAND_ERROR;
    returnCommand.Command = NO_COMMAND;

    if (currentState == STATE_None)
    {
        logger->QuickLog("StewardService> Checking for command from CCMS");

        genStubHeader();

        /*
        Okay, unfortunately, gSOAP turns the data-types inside out. So this can
        get a bit hairy. We must re-construct these somewhat backwards.
        Start out at the lowest possible data type
        */

        // Set up our order num
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ordernum_kv;
        ordernum_kv.Key = "ORDER_NUM";
        ordernum_kv.Value = order_num;

        /*
        Bring it up to the next level
        */

        int numParams = 1;
        if(hostname != NULL)
            numParams++;
        if(hwaddr != NULL)
            numParams++;

        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ar[numParams];
        ar[0] = ordernum_kv;

        numParams = 1;

        /*
        If we have a hostname, use it
        */
        if(hostname != NULL) {
            // Set up our host name
            _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring hostname_kv;
            hostname_kv.Key = "HOST_NAME";
            hostname_kv.Value= hostname;
            ar[numParams] = hostname_kv;
            numParams++;
        }

        /*
        If we have a hwaddr, use it
        */
        if(hwaddr != NULL) {
            // Set up our hwaddr
            _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring hwaddr_kv;
            hwaddr_kv.Key = "MAC_ADDR";
            hwaddr_kv.Value= hwaddr;
            ar[numParams] = hwaddr_kv;
            numParams++;
        }

        /*
        Take that array, and plug it into the next data type level
        */
        ns5__ArrayOfKeyValueOfstringstring k1;
        k1.__sizeKeyValueOfstringstring = numParams;
        k1.KeyValueOfstringstring = &ar[0];

        /*
        Now, up to the machine context
        */
        ns4__MachineContext ctx;
        ctx.mParams = &k1;

        ns4__MachineType l_mType = ns4__MachineType__HOST;

        switch (mType)
        {
            case ANY:
                l_mType = ns4__MachineType__ANY;
                break;
            case HOST_WILDCARD:
                l_mType = ns4__MachineType__HOST_USCOREWILDCARD;
                break;
            case FQDN:
                l_mType = ns4__MachineType__FQDN;
                break;
            case UUID:
                l_mType = ns4__MachineType__UUID;
                break;
            case COLLECTION:
                l_mType = ns4__MachineType__COLLECTION;
                break;
            default:
                // Default is HOST
                l_mType = ns4__MachineType__HOST;
                break;
        }

        ctx.mType = &l_mType;

        // Call the various private methods to for query commands
        if(hostname == NULL) {
            header.wsa5__Action = EIL__GETCOMMANDTOEXECUTEUSINGMACADDRESS;
            synHeaders();

            queryForClientCommands_byHWAddr(&ctx, &returnCommand);
        } else {
            header.wsa5__Action = EIL__GETCOMMANDTOEXECUTE;
            synHeaders();

            queryForClientCommands_byHostname(&ctx, &returnCommand);
        }

        // FIXME Memory clean-up
    }
    else
    {
        // We were in the wrong state to call this method
        returnCommand.ReturnState = COMMAND_ERROR_STATE;
        returnCommand.Command = NO_COMMAND;
    }
    return returnCommand;
}

bool StewardService::UpdateAssetInformation(
            char *hostname,
            char *hwaddr,
            char *assetInfo)
{
    if (currentState == STATE_None)
    {
        logger->QuickLog("StewardService> Update asset information with CCMS");
        genStubHeader();
        header.wsa5__Action = EIL__UPDATEASSETINFO;
        synHeaders();

        /*
         * Set up our update class
         */
        _ns1__UpdateAssetInformation update;
        update.hostName = hostname;
        update.macAddr = hwaddr;
        update.xmlAssetInfo = assetInfo;

        /*
         * Set up our response class
         */
        _ns1__UpdateAssetInformationResponse response;

        /*
         * The actual soap call
         */
        op_codes = service.UpdateAssetInformation(
            &update, &response);

        /*
         * Process the response
         */
        if(op_codes == SOAP_OK) {
            // Soap call was a success, check the response
            if(response.UpdateAssetInformationResult) {
                // Total success, rockin!
                logger->QuickLog("StewardService> Asset information successfully updated to CCMS");
                return true;
            }
            // Hmm, something happened
            logger->QuickLog("StewardService> An error occured with CCMS when trying to update asset information!");
            logger->QuickLog("StewardService> Asset information will not be resubmitted unless a request is made!");
            return false;
        } else {
            /*
             * We have a SOAP error, unfortunately, we can do little with it
             * here because we aren't in a proper command state, so, we log it
             * and return false.
             */
            CCMS_Command returnCommand;
            logger->QuickLog("StewardService> SOAP error while in asset update logic! Recovery not possible!");
            parseOpCode(&returnCommand);
            return false;
        }
    } else {
        // We're in the wrong state for this
        logger->QuickLog("StewardService> Attempt to update asset information while in wrong service state!");
        return false;
    }
}

    /**** Private Methods ****/

void StewardService::getNewMessageID()
{
    char messageID[MAX_MESSAGEID_LEN - 10];

    generateUniqueHash(messageID, MAX_MESSAGEID_LEN - 10);

    // FIXME, it would be nice to have this formatted more like
    // other messageIDs, e.g.,
    // urn:uuid:8d1d259a-bd87-4e9a-b28d-02c4bd420fb3
    snprintf(last_MessageID, MAX_MESSAGEID_LEN,
            "urn:uuid:%s", messageID);
}

void StewardService::queryForClientCommands_byHostname(
            ns4__MachineContext *ctx,
            CCMS_Command *returnCommand)
{
    _ns1__GetCommandToExecute getCommand;
    getCommand.ctx = ctx;

    _ns1__GetCommandToExecuteResponse response;

    /*
    Execute the getCommand request
    */
    op_codes = service.GetCommandToExecute(
        &getCommand, &response);

    /*
    Process the response
    */
    if(op_codes == SOAP_OK) {
        if (response.GetCommandToExecuteResult == NULL) {
            currentState = STATE_None;
            returnCommand->ReturnState = COMMAND_SUCCESS;
            returnCommand->Command = NO_COMMAND;
            logger->QuickLog("StewardService> No command");
        } else {
            // FIXME - Do we want to deal with op_codes here as well?
            parseCommandFromCCMS(ctx,
                response.GetCommandToExecuteResult,
                returnCommand);
        }
    } else {
        parseOpCode(returnCommand);
    }
}

void StewardService::queryForClientCommands_byHWAddr(
            ns4__MachineContext *ctx,
            CCMS_Command *returnCommand)
{
    _ns1__GetCommandToExecuteUsingMacAddress getCommand;
    getCommand.ctx = ctx;

    _ns1__GetCommandToExecuteUsingMacAddressResponse response;

    /*
    Execute the getCommand request
    */
    op_codes = service.GetCommandToExecuteUsingMacAddress(
        &getCommand, &response);

    /*
    Process the response
    */
    if(op_codes == SOAP_OK) {
        if (response.GetCommandToExecuteUsingMacAddressResult == NULL) {
            currentState = STATE_None;
            returnCommand->ReturnState = COMMAND_SUCCESS;
            returnCommand->Command = NO_COMMAND;
            logger->QuickLog("StewardService> No command");
        } else {
            /*
            Be sure to update the header with the proper HTTP SOAP
            action! (or else we will get an "ActionMismatch" error)
            */
            header.wsa5__Action = EIL__UPDATECOMMANDSTATUS;
            synHeaders();

            /*
            First we need to get our responses ready
            */
            _ns1__UpdateCommandStatus updateCmdStat;
            ns4__EILCommand cmd;
            _ns1__UpdateCommandStatusResponse updateCmdStatResp;

            updateCmdStat.ctx = ctx;

            // Parse *what* our command was
            if(strcasecmp(
                response.GetCommandToExecuteUsingMacAddressResult->CommandName,
                CCMS_REBOOT) == 0)
            {
                currentState = STATE_ExecutingCommand;
                returnCommand->ReturnState = COMMAND_SUCCESS;
                returnCommand->Command = REBOOT;

                ns4__EILCommandStatus complete =
                    ns4__EILCommandStatus__COMMAND_USCOREEXECUTION_USCORECOMPLETE;
                int errorcode = 0;
                cmd.CommandResult = "Reboot Successful";
                cmd.CommandStatus = &complete;
                cmd.ErrorCode = &errorcode;
                cmd.CommandName =
                    response.GetCommandToExecuteUsingMacAddressResult->CommandName;

                updateCmdStat.cmd = &cmd;
                updateCmdStat.cmd->OperationID =
                    response.GetCommandToExecuteUsingMacAddressResult->OperationID;

                // FIXME - Do we want to deal with op_codes here as well?
                service.UpdateCommandStatus(
                    &updateCmdStat, &updateCmdStatResp);
            } // Other commands go here
            else
            {
                currentState = STATE_None;
                returnCommand->ReturnState = COMMAND_ERROR;
                returnCommand->Command = NO_COMMAND;
            }
        }
    } else {
        parseOpCode(returnCommand);
    }
}

void StewardService::synHeaders()
{
    service.soap_header(
        header.wsa5__MessageID,
        header.wsa5__RelatesTo,
        header.wsa5__From,
        header.wsa5__ReplyTo,
        header.wsa5__FaultTo,
        header.wsa5__To,
        header.wsa5__Action);
}

void StewardService::genStubHeader()
{
    /*
    First, we need to build up our header, which includes the various
    WS-Addressing bits that are needed by CCMS for routing of commands
    */
    soap_default_SOAP_ENV__Header(&soap, &header);

    soap_default_wsa5__EndpointReferenceType(&soap, &replyTo);
    replyTo.Address = WSA5__ADDRESS_ANONYMOUS;

    getNewMessageID();

    header.wsa5__MessageID = last_MessageID;

    header.wsa5__ReplyTo = &replyTo;
    header.wsa5__To = EIL__CLIENTOPSERVICE;

    soap.header = &header;
}