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
#include <string>

#define HOSTNAME_LEN 50

// Nasty gSOAP bindings
//#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "soapH.h"

// Various helper libraries
#include "logger.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Misc variables to be used by the daemon
    pid_t pid, sid;
    FILE *logPipe;
    //int op_codes;

    char hostname[HOSTNAME_LEN];

    // The CCMS log related variables
    char ccmsLogCommand[]="/usr/bin/clientagent-helper.sh --ccmslog";
    // We assume an upper limit of 256 characters for full path plus
    // filename, perhaps this is bad?
    char logFile[256];

    // Our various SOAP/WSDL/CCMS related items
    struct soap soap;
    //WSHttpBinding_USCOREIEILClientOperationsProxy service;

    // Since we're a daemon, let's start by forking from parent
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // Exit if we have an acceptable pid
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // File mode mask so we can have full access
    umask(0);

    // Obtain the CCMS log file
    if ( !(logPipe = (FILE*)popen(ccmsLogCommand,"r")) )
    {  // If logPipi is NULL
        perror("Problems with pipe to clientagent-helper.sh");
        exit(1);
    }

    while (fgets(logFile, sizeof logFile, logPipe))
    {
        // May be silly to have a loop that does nothing, but
        // we really only expect one result from this pipe
    }
    pclose(logPipe);

    StewardLogger logger(logFile);

    logger.QuickLog("Startup daemon");

    // Obtain a new session ID for child process
    sid = setsid();
    if (sid < 0) {
        logger.QuickLog(
            "Could not obtain new session ID for child process");
        exit(EXIT_FAILURE);
    }

    logger.QuickLog("New Session ID obtained");

    // Obtain our hostname information for the first time
    gethostname(hostname, HOSTNAME_LEN);

    logger.QuickLog("Hostname obtained");

    // TODO - Change to working directory
    // should be determined by a helper script from the dispatcher

    // File descriptors are a security hazard in a daemon
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    logger.QuickLog("STD i/o closed");

    // TODO - Any initialization will go here
    soap_init(&soap); // initialize runtime environment

    logger.QuickLog("gSOAP initialized");

    // Main loop
    while (1) {
        //logger.BeginLogging();
        //logger.LogEntry("Starting Linux Client Agent activity");
        logger.QuickLog("ping0");
        // TODO - Our logic here

        // Generate a command to execute out instance which has proper
        // credentials
        //_ns1__GetCommandToExecute gcte_out;
        logger.QuickLog("ping1");
        //_ns1__GetCommandToExecuteResponse *commandToExecResp;
        logger.QuickLog("ping2");
        //_ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring kvp[1];
        logger.QuickLog("ping3");
        //kvp[0].Key = &string("HOST_NAME");
        logger.QuickLog("ping4");
        //kvp[0].Value = &string("LENM58P-Ubuntu01"); // FIXME
        logger.QuickLog("ping5");

        //_ns5__ArrayOfKeyValueOfstringstring kvpa;
        logger.QuickLog("ping6");
        //kvpa.__sizeKeyValueOfstringstring=1;
        logger.QuickLog("ping7");
        //kvpa.KeyValueOfstringstring = kvp;
        logger.QuickLog("ping8");
        //gcte_out.ctx->mParams = &kvpa;
        logger.QuickLog("ping9");

        //_ns1__GetCommandToExecute gcte(
            //&soap, ns4__MachineContext(
                //ns5__ArrayOfstring,
                //ns5__ArrayOfstring,
                //kvpa,
                //ns4__MachineType__ANY
                //)
            //);

        //op_codes = service.GetCommandToExecute(
            //&gcte, commandToExecResp);
        logger.QuickLog("ping10");
        //logger.LogEntry("Sleeping for 30 seconds");
        //logger.EndLogging();
        sleep(30); // TODO - Our sleep
        // TODO signal to interrupt and break from this loop
    }

    soap_destroy(&soap); // remove deserialized class instances (C++ only)
    soap_end(&soap); // clean up and remove deserialized data
    soap_done(&soap); // detach environment (last use and no longer in scope)
}
