/*
 nmsaService.cpp
 ------------------
 A basic helper class which wraps the service bindings for the NMSA interface
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "logger.h"
#include "nmsaService.h"

NMSA_Service::NMSA_Service(StewardLogger *myLogger)
{
    logger = myLogger;
    logger->QuickLog("NMSA_Service> Initializing the NMSA service");

    enabled = false;
    registered = false;

    struct stat buf;
    if(stat(NMSA_TOGGLE, &buf) == 0) {
        enabled = true;
    }

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
