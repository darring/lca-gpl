/*
   clientagent_helper.cpp
   ----------
   Interface for the client agent helper script provided by the dispatcher
 */

#include <stdlib.h>

#include "clientagent_helper.h"

ClientAgentHelper::ClientAgentHelper()
{
    // TODO anything here?
}

ClientAgentHelper::~ClientAgentHelper()
{
    // TODO cleanup
}

void ClientAgentHelper::Get(
    char *result, int size, ClientAgentOptions option)
{
    char *helperCmd;
    switch (option)
    {
        case CCMSLOG:
            helperCmd = "/usr/bin/clientagent-helper.sh --ccmslog";
            break;
        default:
            // default is PIDFILE
            helperCmd = "/usr/bin/clientagent-helper.sh --pidfile";
            break;
    }

    if ( !(filePipe = (FILE*)popen(helperCmd,"r")) )
    {  // If filePipe is NULL
        perror("Problems with pipe to clientagent-helper.sh");
        exit(1);
    }

    while (fgets(result, size, filePipe))
    {
        // May be silly to have a loop that does nothing, but
        // we really only expect one result from this pipe
    }
    pclose(filePipe);
}
