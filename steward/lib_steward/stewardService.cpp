/*
 stewardService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the gSOAP interfaces
 */

// Nasty gSOAP bindings
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "soapH.h"

#include "logger.h"
#include "stewardService.h"

StewardService::StewardService(StewardLogger *myLogger)
{
    logger = myLogger;
    logger->QuickLog("StewardService> Initializing the steward service");

    // TODO Initialization here
    currentState = STATE_None;

    logger->QuickLog("StewardService> Service initialized...");
}

StewardService::~StewardService()
{
    //soap_destroy(soap); // remove deserialized class instances (C++ only)
    //soap_end(soap); // clean up and remove deserialized data
    //soap_done(soap); // detach environment (last use and no longer in scope)
}

CommandIssued StewardService::QueryForClientCommands(
            char *hostname,
            char *order_num,
            MachineType mType)
{
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

    // Set up our order num
    _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ordernum_kv;
    std::string onumkey = std::string("ORDER_NUM");
    ordernum_kv.Key = &onumkey;
    std::string onumval = std::string(order_num);
    ordernum_kv.Value = &onumval;

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
    _ns1__GetCommandToExecuteResponse response;
    op_codes = service.GetCommandToExecute(
        &getCommand, &response);

    return COMMAND_ERROR;
}
