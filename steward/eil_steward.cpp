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

#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"

int main(int argc, char *argv[])
{
    // Misc variables to be used by the daemon
    pid_t pid;
    FILE *logPipe;

    // The CCMS log related variables
    char *ccmsLogCommand="/usr/bin/clientagent-helper.sh --ccmslog";
    // We assume an upper limit of 256 characters for full path plus
    // filename, perhaps this is bad?
    char logFile[256];

    // The Client Operations Proxy for talking to CCMS
    WSHttpBinding_USCOREIEILClientOperationsProxy service;

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
    if ( !(logPipe = (FILE*)popen(command,"r")) )
    {  // If fpipe is NULL
        perror("Problems with pipe to clientagent-helper.sh");
        exit(1);
    }

    while (fgets(logFile, sizeof logFile, logPipe))
    {
    }
    pclose(logPipe);

    // Open our CCMS log file for appending, creating if it is not there

    // Obtain a new session ID for child process
    sid = setsid();
    if (sid < 0) {
        // TODO - Log failure
        exit(EXIT_FAILURE);
    }

    // TODO - Change to working directory
    // should be determined by a helper script from the dispatcher

    // File descriptors are a security hazard in a daemon
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // TODO - Any initialization will go here

    // Main loop
    while (1) {
        // TODO - Our logic here
        sleep(30); // TODO - Our sleep
    }
}
