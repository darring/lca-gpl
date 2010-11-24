/*
 * stewardService.h
 */

/*! \mainpage Steward service wrapper for the EIL Linux Client Agent
 *
 * \section Introduction Introduction
 *
 * \section Usage Usage
 *
 */

#ifndef stewardService_H
#define stewardService_H

// Helper enumerations
#include "machineType.h"
#include "commands.h"
#include "serviceState.h"

// Proxy service definition
#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"

class StewardLogger;

class StewardService
{
    private:
        WSHttpBinding_USCOREIEILClientOperationsProxy service;
        StewardLogger *logger;
        int op_codes;
        char *last_MessageID;
        ServiceState currentState;

    public:
        //! Constructor for the Steward service wrapper
        /*!
         * \param myLogger is the logger instance we should use.
         */
        StewardService(StewardLogger *myLogger);

        //! Destructor for the Steward service wrapper
        ~StewardService();

        //! Query for client commands from the web service
        /*!
         * Call this every NN seconds to query the web service for available
         * commands.
         * \param hostname is the hostname of this particular machine
         * \param order_num is the value of the ORDER_NUM field
         * \param mType is the Machine Type
         * \return Command type (or error if an error occured)
         *
         */
        CommandIssued QueryForClientCommands(
            char *hostname,
            char *order_num,
            MachineType mType);
};

#endif
