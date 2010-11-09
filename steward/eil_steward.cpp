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

#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"

int main(int argc, char *argv[])
{
    // The Client Operations Proxy for talking to CCMS
    WSHttpBinding_USCOREIEILClientOperationsProxy service;

    pid_t pid;

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

    // TODO - Logging?

    // Obtain a new session ID for child process
    sid = setsid();
    if (sid < 0) {
        // TODO - Log failure
        exit(EXIT_FAILURE);
    }
}
