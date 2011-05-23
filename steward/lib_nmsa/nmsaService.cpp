/*
 nmsaService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the NMSA interface
 */

#include "logger.h"
#include "nmsaService.h"

NMSA_Service::NMSA_Service(StewardLogger *myLogger)
{
    logger = myLogger;
    logger->QuickLog("NMSA_Service> Initializing the NMSA service");

    // TODO Initialization here

    logger->QuickLog("NMSA_Service> Service initialized...");
}

NMSA_Service::~NMSA_Service()
{
    // TODO
}

void NMSA_Service::nmsa_register(char *hwAddr, char *hostname, char *bmc, char *bridge, char *trans)
{
    // TODO
}

void NMSA_Service::Poll(char *hwAddr, char *hostname)
{
    // TODO
}
