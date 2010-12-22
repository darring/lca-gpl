/*
   dispatcher_helper.cpp
   ---------------------
   Abstract interface to the dispatcher shell script
 */

#include "dispatcher_helper.h"

DispatcherHelper(char *binaryPath, char *commandPath,  StewardLogger *myLogger)
{
    binPath = binaryPath;
    comPath = commandPath;
    logger = myLogger;
    logger->QuickLog("DispatcherHelper> Initializing the dispatcher helper");

    char fullDispatcherPath[512]; // This is probably pretty crazy
    snprintf(fullDispatcherPath, 512, "%s/clientagent-dispatcher.sh", binPath);
    dispatcherPath = fullDispatcherPath;
}

~DispatcherHelper()
{
    // TODO cleanup
}

void ExecuteCommand(CCMS_Command *commandIssued)
{
    // It never hurts to have redundancy
    if(commandIssued->ReturnState == COMMAND_SUCCESS)
    {
        switch (commandIssued->Command)
        {
            case REBOOT:
                logger->QuickLog("DispatcherHelper> Reboot command requested");
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
