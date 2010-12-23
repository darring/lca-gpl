/*
   dispatcher_helper.cpp
   ---------------------
   Abstract interface to the dispatcher shell script
 */

#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "dispatcher_helper.h"

DispatcherHelper::DispatcherHelper(char *binaryPath, char *commandPath,  StewardLogger *myLogger)
{
    binPath = binaryPath;
    comPath = commandPath;
    logger = myLogger;
    logger->QuickLog("DispatcherHelper> Initializing the dispatcher helper");

    char fullDispatcherPath[512]; // This is probably pretty crazy
    snprintf(fullDispatcherPath, 512, "%s/clientagent-dispatcher.sh", binPath);
    dispatcherPath = fullDispatcherPath;
    logger->QuickLog(dispatcherPath);
    logger->QuickLog("DispatcherHelper> ping01");
}

DispatcherHelper::~DispatcherHelper()
{
    // TODO cleanup
}

Dispatcher_Command_Status DispatcherHelper::runDispatcher()
{
    char result[50];
    Dispatcher_Command_Status commandStatus;

    if ( !(filePipe = (FILE*)popen(dispatcherPath,"r")) )
    {  // If filePipe is NULL
        logger->QuickLog("DispatcherHelper> Could not execute dispatcher!");
        exit(1);
    }

    while (fgets(result, 50, filePipe))
    {
        // May be silly to have a loop that does nothing, but
        // we really only expect one result from this pipe
    }
    pclose(filePipe);

    // TODO interpret a command status for other commands
    commandStatus.Success = true;

    return commandStatus;
}

void DispatcherHelper::ExecuteCommand(CCMS_Command *commandIssued)
{
    // It never hurts to have redundancy
    if(commandIssued->ReturnState == COMMAND_SUCCESS)
    {
        switch (commandIssued->Command)
        {
            case REBOOT:
                logger->QuickLog("DispatcherHelper> Reboot command requested");
                char rebootCmd[512];
                snprintf(rebootCmd, 512, "%s/reboot", comPath);
                if ( !(filePipe = (FILE*)fopen(rebootCmd, "w")) )
                {
                    logger->QuickLog("DispatcherHelper> Could not open reboot command directory for writing!");
                    exit(1);
                }
                // For reboot, this could be anything
                fputc(0, filePipe);
                fclose(filePipe);

                runDispatcher();
                break;
            default:
                // NO_COMMAND
                /*
                 * Honestly, we shouldn't even be in here if there was no
                 * command issuded, but we'll check for it anyway, and pass.
                 */
                break;
        }
    }
}
