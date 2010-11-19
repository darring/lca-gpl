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
};

#endif
