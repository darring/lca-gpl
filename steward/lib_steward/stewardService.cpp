/*
 stewardService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the gSOAP interfaces
 */

#include "stewardService.h"

StewardService::StewardService(StewardLogger *myLogger)
{
    logger = myLogger;
    // Initialize our soap runtime environment
    soap_init(&soap);
}