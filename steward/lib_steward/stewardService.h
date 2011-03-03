/*
 * stewardService.h
 */

/*! \mainpage Steward service wrapper for the EIL Linux Client Agent
 *
 * \section Introduction Introduction
 *  This is the service wrapper for the steward in the EIL Linux Client agent.
 * The main purpose of this service wrapper is to serve as a barrier between the
 * gSOAP interfaces (which may change based upon the upstream SOAP server's
 * whims) and the rest of the steward and client agent.
 *
 *  We isolate the gSOAP calls and interfaces in this service wrapper to
 * minimize where changes must be made in the event that radical external
 * changes occur that would otherwise affect the client agent in adverse ways.
 *
 * \section Usage Usage
 *  To use the steward service, create an instance of the class StewardServce,
 * and call the StewardService::QueryForClientCommands method every NN seconds
 * (where NN is determined by some external criteria).
 *
 * \section subsections Subsections
 *
 * \li \subpage ccms_commands "CCMS Command Defines"

 */

#ifndef stewardService_H
#define stewardService_H

// Helper enumerations
#include "machineType.h"
#include "commands.h"
#include "serviceState.h"

// Proxy service definition
#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "soapH.h"

//! The maximum length of the MessageID
#define MAX_MESSAGEID_LEN 40

//! The lower character range for the convert method
#define LOWER_CHAR_RANGE 40

//! The upper character range for the convert method
#define UPPER_CHAR_RANGE 126

class StewardLogger;

class StewardService
{
    private:
        WSHttpBinding_USCOREIEILClientOperationsProxy service;
        struct soap soap;
        struct SOAP_ENV__Header header;
        StewardLogger *logger;
        int op_codes;
        char last_MessageID[MAX_MESSAGEID_LEN];
        ServiceState currentState;

        //! Obtain a new message ID
        /*!
         * Internal method used to obtain a valid message ID used in WS-A
         * \return Null byte terminated message ID
         */
        void getNewMessageID();

        //! Internal method for querying client commands by hostname
        /*!
         * \param ctx the machine context used for the call
         * \param returnCommand the CCMS return command struct
         * 
         * \remarks It is assumed that header information has already been set
         * up and all other state data for service has been preset.
         */
        void queryForClientCommands_byHostname(
            ns4__MachineContext *ctx,
            CCMS_Command *returnCommand);

        //! Internal method for querying client commands by HW address
        /*!
         * \param ctx the machine context used for the call
         * \param returnCommand the CCMS return command struct
         *
         * \remarks It is assumed that header information has already been set
         * up and all other state data for service has been preset.
         */
        void queryForClientCommands_byHWAddr(
            ns4__MachineContext *ctx,
            CCMS_Command *returnCommand);

        //! Internal method for parsing the opcode from various calls
        /*!
         * This method is intended to be highly generic, and should only be
         * used when your local method has exhausted all custom opcode
         * interpretations it has. Once called, it will parse the opcode,
         * set the returnCommand and log as appropriate.
         * \param returnCommand the CCMS return command struct
         *
         * \remarks It is assumed that op_codes has been set previously by one
         * of the various calls to the service.
         */
        void parseOpCode(
            CCMS_Command *returnCommand);

        //! Internal method for sync'ing the headers
        void synHeaders();

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
         * \param hwaddr is the hardware address of this particular machine
         * \param order_num is the value of the ORDER_NUM field
         * \param mType is the Machine Type
         * \return Command type (or error if an error occured)
         *
         * \remarks One of hostname of hwaddr is required. The other may be
         * NULL, and will not be used.
         *
         */
        CCMS_Command QueryForClientCommands(
            char *hostname,
            char *hwaddr,
            char *order_num,
            MachineType mType);
};

#endif
