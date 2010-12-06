/*
 sighandlers.cpp
 ------------------
 Collection of signal handlers for EIL Linux Client Agent (steward)
 */

#include <signal.h>
#include <unistd.h>

#include "sighandlers.h"
#include "serviceState.h"

void setupSignalHandlers()
{
    static bool hasSetup = false;
    if(!hasSetup)
    {
        struct sigaction act_SIGHUP, act_SIGINT, act_SIGTERM, act_OLD;

        // Set up SIGHUP
        act_SIGHUP.sa_handler = handle_SIGHUP;
        sigemptyset (&act_SIGHUP.sa_mask);
        act_SIGHUP.sa_flags = 0;

        sigaction (SIGHUP, NULL, &act_OLD);
        if (act_OLD.sa_handler != SIG_IGN)
            sigaction (SIGHUP, &act_SIGHUP, NULL);
        else
        {
            sigaction (SIGHUP, &act_SIGHUP, &act_OLD);
        }

        // Set up SIGINT
        act_SIGINT.sa_handler = handle_SIGINT;
        sigemptyset (&act_SIGINT.sa_mask);
        act_SIGINT.sa_flags = 0;

        sigaction (SIGINT, NULL, &act_OLD);
        if (act_OLD.sa_handler != SIG_IGN)
            sigaction (SIGINT, &act_SIGINT, NULL);
        else
        {
            sigaction (SIGINT, &act_SIGINT, &act_OLD);
        }

        // Set up SIGTERM
        act_SIGTERM.sa_handler = handle_SIGTERM;
        sigemptyset (&act_SIGTERM.sa_mask);
        act_SIGTERM.sa_flags = 0;

        sigaction (SIGTERM, NULL, &act_OLD);
        if (act_OLD.sa_handler != SIG_IGN)
            sigaction (SIGTERM, &act_SIGTERM, NULL);
        else
        {
            sigaction (SIGTERM, &act_SIGTERM, &act_OLD);
        }
    }
}

void handle_SIGHUP(int sig)
{
    S_STATE = S_STATE_Shutdown;
}

void handle_SIGINT(int sig)
{
    S_STATE = S_STATE_Shutdown;
}

void handle_SIGTERM(int sig)
{
    S_STATE = S_STATE_Terminate;
}
