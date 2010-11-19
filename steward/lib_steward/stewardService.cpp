/*
 stewardService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the gSOAP interfaces
 */

// Nasty gSOAP bindings
#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
//#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "soapH.h"

#include "logger.h"
#include "stewardService.h"

StewardService::StewardService(StewardLogger *myLogger)
{
    logger = myLogger;
    // Initialize our soap runtime environment
    soap_init(&soap);
}