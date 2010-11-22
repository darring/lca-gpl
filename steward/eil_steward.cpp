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
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#define HOSTNAME_LEN 50

//! Debugging toggle- Enable to force not to run as daemon
#define DEBUG

/*
// Nasty gSOAP bindings
#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "soapH.h"*/

// Various helper libraries
#include "logger.h"
#include "stewardService.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Misc variables to be used by the daemon
    #ifndef DEBUG
    pid_t pid, sid;
    #endif
    FILE *logPipe;
    //int op_codes;

    char hostname[HOSTNAME_LEN];

    // The CCMS log related variables
    char ccmsLogCommand[]="/usr/bin/clientagent-helper.sh --ccmslog";
    // We assume an upper limit of 256 characters for full path plus
    // filename, perhaps this is bad?
    char logFile[256];

    // Our various SOAP/WSDL/CCMS related items
    //struct soap soap;
    //WSHttpBinding_USCOREIEILClientOperationsProxy service;

    #ifndef DEBUG
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

    #ifndef DEBUG
    // Obtain a new session ID for child process
    sid = setsid();
    if (sid < 0) {
        logger.QuickLog(
            "Could not obtain new session ID for child process");
        exit(EXIT_FAILURE);
    }

    logger.QuickLog("New Session ID obtained");
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

    // TODO - Any initialization will go here
    // Set up our steward service
    logger.QuickLog("Initializing service...");
    StewardService service(&logger);
    
    // Main loop
    while (1) {
        //logger.BeginLogging();
        //logger.LogEntry("Starting Linux Client Agent activity");
        logger.QuickLog(hostname);
        // TODO - Our logic here

        // Set up our hostname
        // Start out at the lowest possible data type
        //_ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring i1;

        logger.QuickLog("ping1");
        //std::string kn = std::string("HOST_NAME");
        //i1.Key = &kn;
        logger.QuickLog("ping2");
        //std::string hn = std::string(hostname);
        //i1.Value= &hn;

        // Set up our order num
        //_ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring on;
        logger.QuickLog("on create");
        //std::string onumkey = std::string("ORDER_NUM");
        //on.Key = &onumkey;
        logger.QuickLog("add key");
        //std::string onumval = std::string("1");
        //on.Value = &onumval;
        logger.QuickLog("add value");

        //_ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring ar[2];
        //ar[0] = i1;
        //ar[1] = on;

        logger.QuickLog("ping3");
        // Move up one data type
        //ns5__ArrayOfKeyValueOfstringstring k1;
        logger.QuickLog("ping4");
        //k1.__sizeKeyValueOfstringstring = 2;
        logger.QuickLog("ping5");
        //k1.KeyValueOfstringstring = &ar[0];
        logger.QuickLog("ping6");

        // Now, up to the machine context
        //ns4__MachineContext ctx;
        logger.QuickLog("ping7");
        //ctx.soap_default(&soap);
        logger.QuickLog("ping8");
        //ctx.mParams = &k1;

        logger.QuickLog("ping9");
        // Now, up to the get command to execute class
        //_ns1__GetCommandToExecute getCommand;
        logger.QuickLog("ping10");
        //getCommand.ctx = &ctx;
        logger.QuickLog("ping11");
        //getCommand.soap_serialize(&soap);
        logger.QuickLog("ping12");
        //soap_begin_send(&soap);
        logger.QuickLog("ping13");
        //op_codes = getCommand.soap_put(&soap, "ns:element-name", "ns:type-name");
        //_ns1__GetCommandToExecuteResponse response;
        //op_codes = service.GetCommandToExecute(
        //    &getCommand, &response);
        logger.QuickLog("ping14");
        //soap_end_send(&soap);

        //if(op_codes == SOAP_OK)
        //    logger.QuickLog("SOAP_OK");
        //else if (op_codes == SOAP_EOF)
        //    logger.QuickLog("SOAP_EOF");
        //else if (op_codes == SOAP_SVR_FAULT)
        //    logger.QuickLog("SOAP_SVR_FAULT");
        //else if (op_codes == SOAP_MUSTUNDERSTAND)
        //    logger.QuickLog("SOAP_MUSTUNDERSTAND");
        //else {
        //    logger.QuickLog("ERROR!");
        //    char str[20];
        //    snprintf(str, 20, "%d", op_codes);
        //    logger.QuickLog(str);
        //}
        logger.QuickLog("ping15");

        //logger.LogEntry("Sleeping for 30 seconds");
        //logger.EndLogging();
        sleep(30); // TODO - Our sleep
        // TODO signal to interrupt and break from this loop
    }

    //soap_destroy(&soap); // remove deserialized class instances (C++ only)
    //soap_end(&soap); // clean up and remove deserialized data
    //soap_done(&soap); // detach environment (last use and no longer in scope)
}
