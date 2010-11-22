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
    struct soap lsoap;
    logger = myLogger;
    logger->QuickLog("StewardService> gSOAP setup...");
    // Initialize our soap runtime environment
    soap_init(&lsoap);
    soap = &lsoap;
    
    logger->QuickLog("StewardService> gSOAP initialized");
}

StewardService::~StewardService()
{
    soap_destroy(soap); // remove deserialized class instances (C++ only)
    soap_end(soap); // clean up and remove deserialized data
    soap_done(soap); // detach environment (last use and no longer in scope)
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
    ctx.soap_default(soap); // Must set our soap instance
    ctx.mParams = &k1;
    
    /*
      Finally, we're ready for the GetCommandToExecute class
    */
    _ns1__GetCommandToExecute getCommand;
    getCommand.ctx = &ctx;
    getCommand.soap_serialize(soap); // Serialize with our soap instance
    _ns1__GetCommandToExecuteResponse response;
    op_codes = service->GetCommandToExecute(
        &getCommand, &response);

    return COMMAND_ERROR;
}
