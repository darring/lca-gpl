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

// Nasty gSOAP bindings
#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"
#include "WSHttpBinding_USCOREIEILClientOperations.nsmap"
#include "soapH.h"

class StewardService
{
    private:
        struct soap soap;
        WSHttpBinding_USCOREIEILClientOperationsProxy service;
    public:
        //! Constructor for the Steward service wrapper
        /*!
         *
         */
        StewardService();
        
        //! Destructor for the Steward service wrapper
        ~StewardService();
        
        
}

#endif