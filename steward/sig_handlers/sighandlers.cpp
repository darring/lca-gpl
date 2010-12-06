/*
 sighandlers.cpp
 ------------------
 Collection of signal handlers for EIL Linux Client Agent (steward)
 */

#include "sighandlers.h"
#include <signal.h>

void setupSignalHandlers()
{
    static bool hasSetup = false;
    if(!hasSetup)
    {
        struct sigaction act_SIGHUP, act_SIGINT, act_SIGTERM;
    }
}

void handle_SIGHUP(int sig)
{
}

void handle_SIGINT(int sig)
{
}

void handle_SIGTERM(int sig)
{
}