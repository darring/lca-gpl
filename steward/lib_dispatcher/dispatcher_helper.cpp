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

    snprintf(dispatcherPath, 512, "%s/clientagent-dispatcher.sh", binPath);
}

DispatcherHelper::~DispatcherHelper()
{
    // TODO cleanup
}

Dispatcher_Command_Status DispatcherHelper::runDispatcher()
{
    char result[50];
    FILE *filePipe;
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

    commandStatus.Success = true;

    return commandStatus;
}

void DispatcherHelper::writeCommandDirectory(const char *command)
{
    char rebootCmd[512];
    FILE *filePipe;
    snprintf(rebootCmd, 512, "%s/%s", comPath, command);
    if ( !(filePipe = (FILE*)fopen(rebootCmd, "w")) )
    {
        logger->QuickLog("DispatcherHelper> Could not open command directory for writing!");
        exit(1);
    }
    // For this could be anything
    fputc(102, filePipe);
    fclose(filePipe);
}

void DispatcherHelper::ExecuteCommand(CCMS_Command *commandIssued)
{
    // It never hurts to have redundancy
    if(commandIssued->ReturnState == COMMAND_SUCCESS ||
       commandIssued->ReturnState == COMMAND_TCP_ERROR)
    {
        switch (commandIssued->Command)
        {
            case REBOOT:
                logger->QuickLog("DispatcherHelper> Reboot command requested");

                writeCommandDirectory("reboot");

                runDispatcher();
                break;
            case TCP_DIAGNOSE:
                logger->QuickLog("DispatcherHelper> TCP diagnose command requested");

                writeCommandDirectory("tcp_diag");

                runDispatcher();
                break;
            case ASSET_REFRESH:
                logger->QuickLog("DispatcherHelper> Asset refresh command requested");

                writeCommandDirectory("asset_refresh");

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
