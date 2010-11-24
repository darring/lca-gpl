/*
 stewardService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the gSOAP interfaces
 */

// Nasty gSOAP bindings
#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "soapH.h"

#include "logger.h"
#include "stewardService.h"

StewardService::StewardService(StewardLogger *myLogger)
{
    //struct soap lsoap;
    //serviceIsSet = false;
    logger = myLogger;
    logger->QuickLog("StewardService> gSOAP setup...");
    // Initialize our soap runtime environment
    //soap_init(&lsoap);
    //soap = &lsoap;
    
    logger->QuickLog("StewardService> gSOAP initialized");
        
    logger->QuickLog("StewardService> Proxy Service setup...");
    
    //setService(&lservice);
    
    logger->QuickLog("StewardService> Proxy Service initialized...");
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
    WSHttpBinding_USCOREIEILClientOperationsProxy service;

    logger->QuickLog("StewardService> ping1");
    
    // Set up our host name
    _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring hostname_kv;
    logger->QuickLog("StewardService> ping2");
    std::string kn = std::string("HOST_NAME");
    logger->QuickLog("StewardService> ping3");
    hostname_kv.Key = &kn;
    std::string hn = std::string(hostname);
    logger->QuickLog("StewardService> ping5");
    hostname_kv.Value= &hn;
    
    // Set up our order num
    logger->QuickLog("StewardService> ping6");
    _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ordernum_kv;
    logger->QuickLog("StewardService> ping7");
    std::string onumkey = std::string("ORDER_NUM");
    logger->QuickLog("StewardService> ping8");
    ordernum_kv.Key = &onumkey;
    logger->QuickLog("StewardService> ping9");
    std::string onumval = std::string(order_num);
    logger->QuickLog("StewardService> ping10");
    ordernum_kv.Value = &onumval;
    logger->QuickLog("StewardService> ping11");
    
    /*
      Bring it up to the next level
    */
    _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ar[2];
    logger->QuickLog("StewardService> ping12");
    ar[0] = hostname_kv;
    logger->QuickLog("StewardService> ping13");
    ar[1] = ordernum_kv;
    logger->QuickLog("StewardService> ping14");
    
    /*
      Take that array, and plug it into the next data type level
    */
    ns5__ArrayOfKeyValueOfstringstring k1;
    logger->QuickLog("StewardService> ping15");
    k1.__sizeKeyValueOfstringstring = 2;
    logger->QuickLog("StewardService> ping16");
    k1.KeyValueOfstringstring = &ar[0];
    
    /*
      Now, up to the machine context
    */
    logger->QuickLog("StewardService> ping17");
    ns4__MachineContext ctx;
    logger->QuickLog("StewardService> ping18");
    //ctx.soap_default(soap); // Must set our soap instance
    logger->QuickLog("StewardService> ping19");
    ctx.mParams = &k1;
    logger->QuickLog("StewardService> ping20");
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
    logger->QuickLog("StewardService> ping21");
    getCommand.ctx = &ctx;
    logger->QuickLog("StewardService> ping22");
    //getCommand.soap_serialize(soap); // Serialize with our soap instance
    logger->QuickLog("StewardService> ping23");
    _ns1__GetCommandToExecuteResponse response;
    logger->QuickLog("StewardService> ping24");
    op_codes = service.GetCommandToExecute(
        &getCommand, &response);
    logger->QuickLog("StewardService> ping25");

    return COMMAND_ERROR;
}
