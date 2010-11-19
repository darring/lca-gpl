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

#include "machineType.h"
#include "commands.h"

class StewardLogger;
class WSHttpBinding_USCOREIEILClientOperationsProxy;

class StewardService
{
    private:
        struct soap soap;
        WSHttpBinding_USCOREIEILClientOperationsProxy service;
        StewardLogger *logger;
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
        Command QueryForClientCommands(
            char *hostname,
            char *order_num,
            MachineType mType);
};

#endif
