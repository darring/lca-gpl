/*
 uniqueHash.cpp
 ------------------
 A basic helper class which provides unique hashes for the steward library
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "uniqueHash.h"

UniqueHash::UniqueHash()
{
    hashCommand = "/usr/bin/clientagent-helper.sh --hash";
}

UniqueHash::~UniqueHash()
{

}

char* UniqueHash::GetHash()
{
    char hash[256];
    char *retVal;
    FILE *commandPipe;

    if ( !(commandPipe = (FILE*)popen(hashCommand,"r")) )
    {  // If commandPipe is NULL
        perror("Problems with pipe to clientagent-helper.sh");
        exit(1);
    }

    while (fgets(hash, sizeof hash, commandPipe))
    {
        // May be silly to have a loop that does nothing, but
        // we really only expect one result from this pipe
    }
    pclose(commandPipe);

    retVal = hash;
    return retVal;
}
