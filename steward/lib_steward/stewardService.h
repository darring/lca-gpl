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

        //! Convert a string to all lower case
        /*!
         * Internal method used to perform in-place conversion of  a string to
         * all lower case. This method will also NULL any extraneous
         * non-printable characters from the string.
         * \note
         * Note that any non-printable characters found in the middle of the
         * string will be NULL'ed as well, thus terminating the string where
         * the new NULL character was inserted.
         * \param str The string to convert
         */
        void lowerConvert(char *str);

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
