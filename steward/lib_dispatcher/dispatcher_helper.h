/*
 * DispatcherHelper header
 */

/*! \mainpage DispatcherHelper Interface
 *
 * \section intro_sec Introduction
 *
 * This class provides an abstract interface into the dispatcher itself. It is
 * intended to centralize all dispatcher-related calls and interfacing into a
 * single location such that any changes only affect one location.
 *
 * \section TODO_sec TODO
 *
 */

#ifndef dispatcher_helper_H
#define dispatcher_helper_H

#include <stdio.h>

#include "commands.h"

class StewardLogger;

//! Abstract interface to the dispatcher shell script
class DispatcherHelper
{
    private:
        FILE *filePipe;
        char *binPath;
        char *comPath;
        char *dispatcherPath;
        StewardLogger *logger;
    public:
        //! Constructor for the abstract interface to the dispatcher
        /*!
         * \param binaryPath The path to the installed dispatcher binary files
         * \param commandPath The path to the command directory for the dispatcher
         * \param myLogger The logger instance associated with this program
         */
        DispatcherHelper(
            char *binaryPath, char *commandPath, StewardLogger *myLogger);

        //! Destructor for the abstract interface to the dispatcher
        ~DispatcherHelper();

        //! Actually execute the command
        /*!
         * \param commandIssued The CCMS_Command struct containing the command data
         */
        void ExecuteCommand(CCMS_Command *commandIssued);
};

#endif
