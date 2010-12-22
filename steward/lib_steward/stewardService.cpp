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
        /*
        First, we need to build up our header, which includes the various
        WS-Addressing bits that are needed by CCMS for routing of commands
        */
        soap_default_SOAP_ENV__Header(&soap, &header);

        struct wsa5__EndpointReferenceType replyTo;

        soap_default_wsa5__EndpointReferenceType(&soap, &replyTo);
        replyTo.Address = WSA5__ADDRESS_ANONYMOUS;

        getNewMessageID();

        header.wsa5__MessageID = last_MessageID;
        logger->QuickLog(header.wsa5__MessageID);

        header.wsa5__ReplyTo = &replyTo;
        header.wsa5__To = EIL__CLIENTOPSERVICE;

        header.wsa5__Action = EIL__GETCOMMANDTOEXECUTE;

        soap.header = &header;

        /*
        Okay, unfortunately, gSOAP turns the data-types inside out. So this can
        get a bit hairy. We must re-construct these somewhat backwards.
        Start out at the lowest possible data type
        */

        // Set up our host name
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring hostname_kv;
        hostname_kv.Key = "HOST_NAME";
        hostname_kv.Value= hostname;

        // Set up our order num
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ordernum_kv;
        ordernum_kv.Key = "ORDER_NUM";
        ordernum_kv.Value = order_num;

        /*
        Bring it up to the next level
        */
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ar[2];
        ar[0] = hostname_kv;
        ar[1] = ordernum_kv;

        /*
        Take that array, and plug it into the next data type level
        */
        ns5__ArrayOfKeyValueOfstringstring k1;
        k1.__sizeKeyValueOfstringstring = 2;
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

        /*
        Finally, we're ready for the GetCommandToExecute class
        */
        _ns1__GetCommandToExecute getCommand;
        getCommand.ctx = &ctx;

        service.soap_header(
            header.wsa5__MessageID,
            header.wsa5__RelatesTo,
            header.wsa5__From,
            header.wsa5__ReplyTo,
            header.wsa5__FaultTo,
            header.wsa5__To,
            header.wsa5__Action);

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
                returnCommand.ReturnState = COMMAND_SUCCESS;
                returnCommand.Command = NO_COMMAND;
            } else {
                // Parse *what* our command was
                if(strcasecmp(
                    response.GetCommandToExecuteResult->CommandName, "reboot"))
                {
                    currentState = STATE_ExecutingCommand;
                    returnCommand.ReturnState = COMMAND_SUCCESS;
                    returnCommand.Command = REBOOT;
                } // Other commands go here
                else
                {
                    currentState = STATE_None;
                    returnCommand.ReturnState = COMMAND_ERROR;
                    returnCommand.Command = NO_COMMAND;

                }
            }
        } else {
            // FIXME - Might be nice to actually parse for specific error
            // codes, see http://www.cs.fsu.edu/~engelen/soapdoc2.html#tth_sEc10.2
            currentState = STATE_None;
            returnCommand.ReturnState = COMMAND_ERROR;
            returnCommand.Command = NO_COMMAND;
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
