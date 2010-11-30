/*
 stewardService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the gSOAP interfaces
 */

// Nasty gSOAP bindings
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
//#include "soapH.h"
#include "wsaapi.h"

#include "logger.h"
#include "stewardService.h"

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

CommandIssued StewardService::QueryForClientCommands(
            char *hostname,
            char *order_num,
            MachineType mType)
{
    if (currentState == STATE_None)
    {
        /*
        First, we need to build up our header, which includes the various
        WS-Addressing bits that are needed by CCMS for routing of commands
        */
        soap_default_SOAP_ENV__Header(&soap, &header);
        logger->QuickLog("ping1");

        struct wsa5__EndpointReferenceType replyTo;
        logger->QuickLog("ping2");

        soap_default_wsa5__EndpointReferenceType(&soap, &replyTo);
        logger->QuickLog("ping3");
        replyTo.Address = "http://www.w3.org/2005/08/addressing/anonymous";

        logger->QuickLog("ping4");
        header.wsa5__MessageID = getNewMessageID();

        logger->QuickLog("ping5");
        header.wsa5__ReplyTo = &replyTo;
        logger->QuickLog("ping6");
        header.wsa5__To = "http://172.16.3.10/CCMS/EILClientOperationsService.svc"; // FIXME

        logger->QuickLog("ping7");
        header.wsa5__Action = "http://tempuri.org/IEILClientOperations/GetCommandToExecute"; // FIXME

        logger->QuickLog("ping7.5");
        soap.header = &header;

        /*
        Okay, unfortunately, gSOAP turns the data-types inside out. So this can
        get a bit hairy. We must re-construct these somewhat backwards.
        Start out at the lowest possible data type
        */

        // Set up our host name
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring hostname_kv;
        std::string kn = std::string("HOST_NAME");
        hostname_kv.Key = &kn;
        std::string hn = std::string(hostname);
        hostname_kv.Value= &hn;

        logger->QuickLog("ping8");

        // Set up our order num
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ordernum_kv;
        std::string onumkey = std::string("ORDER_NUM");
        ordernum_kv.Key = &onumkey;
        std::string onumval = std::string(order_num);
        ordernum_kv.Value = &onumval;

        logger->QuickLog("ping9");

        /*
        Bring it up to the next level
        */
        _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ar[2];
        ar[0] = hostname_kv;
        ar[1] = ordernum_kv;

        logger->QuickLog("ping10");

        /*
        Take that array, and plug it into the next data type level
        */
        ns5__ArrayOfKeyValueOfstringstring k1;
        k1.__sizeKeyValueOfstringstring = 2;
        k1.KeyValueOfstringstring = &ar[0];

        logger->QuickLog("ping11");

        /*
        Now, up to the machine context
        */
        ns4__MachineContext ctx;
        ctx.mParams = &k1;
        //ctx.soap_default(&soap); // Must set our soap instance
        ns4__MachineType l_mType = ns4__MachineType__HOST;

        logger->QuickLog("ping11");
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

        logger->QuickLog("ping12");

        /*
        Finally, we're ready for the GetCommandToExecute class
        */
        _ns1__GetCommandToExecute getCommand;
        getCommand.ctx = &ctx;

        //ctx.soap_default(&soap); // Must set our soap instance
        //getCommand.soap_default(&soap);

        logger->QuickLog("ping13");

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
        logger->QuickLog("ping14");

        // FIXME Set proper state information here

        // FIXME Return something useful
        return COMMAND_ERROR;
    }
    else
    {
        // We were in the wrong state to call this method
        return COMMAND_ERROR_STATE;
    }

}

    /**** Private Methods ****/

char* StewardService::getNewMessageID()
{
    char *messageID; // Temp place holder

    // FIXME for now we just hardcode this, but later on, we want to
    // generate this more dynamically
    // urn:uuid:75a4a1d6-7d17-48e5-bcfb-83307aeaf321

    messageID = "urn:uuid:75a4a1d6-7d17-48e5-bcfb-83307aeaf321";

    return messageID;
}
