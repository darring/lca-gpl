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
                    response.GetCommandToExecuteResult->CommandName, "reboot")
                    == 0)
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

            // Our default error state, should we not find anything else
            currentState = STATE_None;
            returnCommand.ReturnState = COMMAND_ERROR;
            returnCommand.Command = NO_COMMAND;
            switch (op_codes)
            {
                case SOAP_CLI_FAULT:
                    logger->QuickLog("StewardService> ERROR! SOAP_CLI_FAULT 'The service returned a client fault (SOAP 1.2 Sender fault)'");
                    break;
                case SOAP_SVR_FAULT:
                    logger->QuickLog("StewardService> ERROR! SOAP_SVR_FAULT 'The service returned a server fault (SOAP 1.2 Receiver fault)'");
                    break;
                case SOAP_TAG_MISMATCH:
                    logger->QuickLog("StewardService> ERROR! SOAP_TAG_MISMATCH 'An XML element didn't correspond to anything expected'");
                    break;
                case SOAP_TYPE:
                    logger->QuickLog("StewardService> ERROR! SOAP_TYPE 'XML Schema type mismatch'");
                    break;
                case SOAP_SYNTAX_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_SYNTAX_ERROR 'An XML syntax error occurred on the input'");
                    break;
                case SOAP_NO_TAG:
                    logger->QuickLog("StewardService> ERROR! SOAP_NO_TAG 'Begin of an element expected, but not found'");
                    break;
                case SOAP_IOB:
                    logger->QuickLog("StewardService> ERROR! SOAP_IOB 'Array index out of bounds'");
                    break;
                case SOAP_MUSTUNDERSTAND:
                    logger->QuickLog("StewardService> ERROR! SOAP_MUSTUNDERSTAND 'An element needs to be ignored that need to be understood'");
                    break;
                case SOAP_NAMESPACE:
                    logger->QuickLog("StewardService> ERROR! SOAP_NAMESPACE 'Namespace name mismatch (validation error)'");
                    break;
                case SOAP_FATAL_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_FATAL_ERROR 'Internal error'");
                    break;
                case SOAP_USER_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_USER_ERROR 'User error'");
                    break;
                case SOAP_FAULT:
                    logger->QuickLog("StewardService> ERROR! SOAP_FAULT 'An exception raised by the service'");
                    break;
                case SOAP_NO_METHOD:
                    logger->QuickLog("StewardService> ERROR! SOAP_NO_METHOD '[gSOAP] did not find a matching operation for the request'");
                    break;
                case SOAP_NO_DATA:
                    logger->QuickLog("StewardService> ERROR! SOAP_NO_DATA 'No data in HTTP message'");
                    break;
                case SOAP_GET_METHOD:
                    logger->QuickLog("StewardService> ERROR! SOAP_GET_METHOD 'HTTP GET operation not handled'");
                    break;
                case SOAP_EOM:
                    logger->QuickLog("StewardService> ERROR! SOAP_EOM 'Out of memory'");
                    break;
                case SOAP_MOE:
                    logger->QuickLog("StewardService> ERROR! SOAP_MOE 'Memory overflow/corruption error (DEBUG mode)'");
                    break;
                case SOAP_NULL:
                    logger->QuickLog("StewardService> ERROR! SOAP_NULL 'An element was null, while it is not supposed to be null'");
                    break;
                case SOAP_DUPLICATE_ID:
                    logger->QuickLog("StewardService> ERROR! SOAP_DUPLICATE_ID 'Element's ID duplicated (SOAP encoding)'");
                    break;
                case SOAP_MISSING_ID:
                    logger->QuickLog("StewardService> ERROR! SOAP_DUPLICATE_ID 'Element ID missing for an href/ref (SOAP encoding)'");
                    break;
                case SOAP_HREF:
                    logger->QuickLog("StewardService> ERROR! SOAP_HREF 'Reference to object is incompatible with the object refered to'");
                    break;
                case SOAP_UDP_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_UDP_ERROR 'Message too large to store in UDP packet'");
                    break;
                case SOAP_TCP_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_TCP_ERROR 'A connection error occured'");
                    break;
                case SOAP_HTTP_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_HTTP_ERROR 'An HTTP error occured'");
                    break;
                case SOAP_SSL_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_SSL_ERROR 'An SSL error occured'");
                    break;
                case SOAP_ZLIB_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_ZLIB_ERROR 'A Zlib error occured'");
                    break;
                case SOAP_PLUGIN_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_PLUGIN_ERROR 'Failed to register plugin'");
                    break;
                case SOAP_MIME_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_MIME_ERROR 'MIME parsing error'");
                    break;
                case SOAP_MIME_HREF:
                    logger->QuickLog("StewardService> ERROR! SOAP_MIME_HREF 'MIME attachment has no href from SOAP body error'");
                    break;
                case SOAP_MIME_END:
                    logger->QuickLog("StewardService> ERROR! SOAP_MIME_END 'End of MIME attachments protocol error'");
                    break;
                case SOAP_DIME_ERROR:
                    logger->QuickLog("StewardService> ERROR! SOAP_DIME_ERROR 'DIME parsing error'");
                    break;
                case SOAP_DIME_END:
                    logger->QuickLog("StewardService> ERROR! SOAP_DIME_END 'End of DIME attachments protocol error'");
                    break;
                case SOAP_DIME_HREF:
                    logger->QuickLog("StewardService> ERROR! SOAP_DIME_HREF 'DIME attachment has no href from SOAP body'");
                    break;
                case SOAP_DIME_MISMATCH:
                    logger->QuickLog("StewardService> ERROR! SOAP_DIME_MISMATCH 'DIME version/transmission error'");
                    break;
                case SOAP_VERSIONMISMATCH:
                    logger->QuickLog("StewardService> ERROR! SOAP_VERSIONMISMATCH 'SOAP version mismatch or no SOAP message'");
                    break;
                case SOAP_DATAENCODINGUNKNOWN:
                    logger->QuickLog("StewardService> ERROR! SOAP_DATAENCODINGUNKNOWN 'SOAP 1.2 DataEncodingUnknown fault'");
                    break;
                case SOAP_REQUIRED:
                    logger->QuickLog("StewardService> ERROR! SOAP_REQUIRED 'Attributed required validation error'");
                    break;
                case SOAP_PROHIBITED:
                    logger->QuickLog("StewardService> ERROR! SOAP_PROHIBITED 'Attributed prohibited validation error'");
                    break;
                case SOAP_OCCURS:
                    logger->QuickLog("StewardService> ERROR! SOAP_OCCURS 'Element minOccurs/maxOccurs validation error'");
                    break;
                case SOAP_LENGTH:
                    logger->QuickLog("StewardService> ERROR! SOAP_LENGTH 'Element length validation error'");
                    break;
                case SOAP_FD_EXCEEDED:
                    logger->QuickLog("StewardService> ERROR! SOAP_FD_EXCEEDED 'Too many open sockets'");
                    break;
                case SOAP_EOF:
                    logger->QuickLog("StewardService> ERROR! SOAP_EOF 'Unexpected end of file, no input, or timeout while receiving data'");
                    break;
                case SOAP_ERR:
                    logger->QuickLog("StewardService> ERROR! SOAP_ERR 'General internal error'");
                    break;
                default:
                    logger->QuickLog("StewardService> ERROR! Undefined gSOAP error!");
                    break;
            }
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
