/*
 nmsaService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the NMSA interface
 */

#include "nmsaService.h"

NMSA_Service::NMSA_Service(StewardLogger *myLogger)
{
    logger = myLogger;
    logger->QuickLog("NMSA_Service> Initializing the NMSA service");

    // TODO Initialization here

    logger->QuickLog("NMSA_Service> Service initialized...");
}

~NMSA_Service::NMSA_Service()
{
    // TODO
}
