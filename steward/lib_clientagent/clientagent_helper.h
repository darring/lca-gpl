/*
 * ClientAgentHelper header
 */

/*! \mainpage ClientAgentHelper Interface
 *
 * \section intro_sec Introduction
 *
 * This class provides the interface to the client agent helper scripts provided
 * by the dispatcher.
 *
 * \section TODO_sec TODO
 *
 */

#ifndef clientagent_helper_H
#define clientagent_helper_H

#include <stdio.h>

//! Possible options for the client agent
enum ClientAgentOptions
{
    CCMSLOG,
    PIDFILE,
};

//! Interface for the client agent helper script
class ClientAgentHelper
{
    private:
        FILE *filePipe;
    public:
        //! Constructor for the client agent helper
        ClientAgentHelper();

        //! Destructor for the client agent helper
        ~ClientAgentHelper();

        //! Get a result from the client agent helper
        /*!
         * Given an option, will obtain a result from the client agent helper
         * script.
         *
         * \param result The resultant character string
         * \param size The size of result
         * \param option The client agent option
         */
        void Get(char *result, int size, ClientAgentOptions option);
};

#endif
