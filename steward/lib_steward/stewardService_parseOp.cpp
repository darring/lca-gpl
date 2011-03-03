/*
 * Split out from the main file because this is rather ugly
 */

#include "logger.h"
#include "stewardService.h"
#include "EIL_defines.h"

void StewardService::parseOpCode(
            CCMS_Command *returnCommand)
{
    // These codes are defined here:
    // http://www.cs.fsu.edu/~engelen/soapdoc2.html#tth_sEc10.2

    // Our default error state, should we not find anything else
    currentState = STATE_None;
    returnCommand->ReturnState = COMMAND_ERROR;
    returnCommand->Command = NO_COMMAND;
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
            /*
                This actually could mean a variety of things, however, one
                of the more serious causes is that we have just switched
                VLANs and need to re-up our network interfaces. This is
                beyond the mental faculties of the steward, so we offload
                the workload to an external script to diagnose the problem
                */
            returnCommand->ReturnState = COMMAND_TCP_ERROR;
            returnCommand->Command = TCP_DIAGNOSE;
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
        default:
            logger->QuickLog("StewardService> ERROR! Undefined gSOAP error!");
            break;
    }
}
