/*
 * eil_steward.c
 * -------------
 * Description:
 *  The steward is the thin gSOAP-based application which communicates
 *  with the CCMS, accepts commands, and hands them to the dispatcher
 *  (which is already installed on the system)
 * License Note:
 *  Please see the associated LICENSE file included with the source
 *  repository of this application for special license considerations.
 *  In a nutshell, parts of this application are based upon gSOAP, and
 *  depending upon how it is built (dynamic vs. static linking) it may
 *  also include GNU libc and other LGPL libraries. Care must be given
 *  in redistributing this application, its binary and its source, as
 *  redistribution outside of Intel will result in placing this software
 *  under the GPL for compliance.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define HOSTNAME_LEN 50

//! Debugging toggle- Enable to force not to run as daemon
//#define DEBUG

// Various helper libraries
#include "logger.h"
#include "stewardService.h"
#include "machineType.h"
#include "clientagent_helper.h"
#include "serviceState.h"
#include "dispatcher_helper.h"

//! The current steward system state
static volatile StewardState S_STATE;

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

int main(int argc, char *argv[])
{
    // Misc variables to be used by the daemon
    #ifndef DEBUG
    pid_t pid, sid;
    #endif
    FILE *filePipe;

    char hostname[HOSTNAME_LEN];

    // The CCMS log related variables
    // We assume an upper limit of 256 characters for full path plus
    // filename, perhaps this is bad?
    char logFile[256];

    // The PID related variables
    // Just like the logFile, we assume an upper limit of 256 characters for
    // full path plus filename, could be bad?
    char pidFile[256];
    char pidOut[256];

    // The bin and dispatcher related variables
    char binPath[256];
    char comPath[256];

    ClientAgentHelper agentHelper;
    CCMS_Command issuedCommand;

    #ifndef DEBUG
    // Obtain the PID file
    agentHelper.Get(pidFile, 256, PIDFILE);

    // Since we're a daemon, let's start by forking from parent
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // Exit if we have an acceptable pid
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    #endif
    // File mode mask so we can have full access
    umask(0);

    // Obtain the CCMS log file
    agentHelper.Get(logFile, 256, CCMSLOG);

    // Obtain the bin directory
    agentHelper.Get(binPath, 256, BINDIR);
    agentHelper.Get(comPath, 256, COMDIR);

    #ifndef DEBUG
    StewardLogger logger(logFile);
    #else
    StewardLogger logger(stdout);
    #endif

    logger.BeginLogging();
    logger.LogEntry("EIL Linux Client Agent");
    logger.LogEntry(EIL_VERSION_TEXT);
    logger.LogEntry("Startup daemon");
    logger.EndLogging();

    #ifndef DEBUG
    // Obtain a new session ID for child process
    sid = setsid();
    if (sid < 0) {
        logger.QuickLog(
            "Could not obtain new session ID for child process");
        exit(EXIT_FAILURE);
    }

    logger.QuickLog("New Session ID obtained");
    if ( !(filePipe = (FILE*)fopen(pidFile, "w")) )
    {
        perror("Problems opening PID file for writing!");
        return false;
    }
    snprintf(pidOut, 256, "%d\n", sid);
    fputs(pidOut, filePipe);
    pclose(filePipe);
    #endif

    // Obtain our hostname information for the first time
    gethostname(hostname, HOSTNAME_LEN);

    logger.QuickLog("Hostname obtained");

    // TODO - Change to working directory
    // should be determined by a helper script from the dispatcher

    #ifndef DEBUG
    // File descriptors are a security hazard in a daemon
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    logger.QuickLog("STD i/o closed");
    #endif

    // Set up our steward service
    logger.QuickLog("Initializing service...");

    StewardService service(&logger);

    // Set up our dispatcher handler
    DispatcherHelper dispatcher(binPath, comPath, &logger);

    // Set up signal handling
    logger.QuickLog("Set up signal handlers...");
    setupSignalHandlers();

    /* Sanity checks */
    // Check that hostname isn't localhost
    if (strncmp(hostname, "localhost", 9) == 0) {
        logger.QuickLog("Hostname is set to 'localhost', which is
    }

    S_STATE = S_STATE_Running;

    // Main loop
    while (S_STATE == S_STATE_Running) {
        logger.BeginLogging();
        logger.LogEntry("Starting Linux Client Agent activity");
        logger.QuickLog(hostname);

        issuedCommand = service.QueryForClientCommands(hostname, "1", HOST);

        switch (issuedCommand.ReturnState)
        {
            case COMMAND_ERROR:
                logger.QuickLog("There was a command error!");
                // TODO - Deal with error logic
                break;
            case COMMAND_ERROR_STATE:
                // TODO - This shouldn't happen, need to figure out what to do
                break;
            default:
                // COMMAND_SUCCESS
                if(issuedCommand.Command != NO_COMMAND)
                    dispatcher.ExecuteCommand(&issuedCommand);
                // If no command, we just pass
                break;
        }

        logger.LogEntry("Sleeping for 30 seconds");
        logger.EndLogging();
        sleep(30);
    }

    logger.QuickLog("Signal caught, exit steward...");
    if (S_STATE == S_STATE_Shutdown)
    {
        // We have time, let's do this right
        service.~StewardService();
        logger.EndLogging();
        logger.~StewardLogger();
    }

    unlink(pidFile);
}
