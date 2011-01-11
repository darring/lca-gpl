/*
 * nmsaService.h
 */

/*! \mainpage NMSA service wrapper for the EIL Linux Client Agent
 *
 * \section Introduction Introduction
 *
 * \section Usage Usage
 *
 */

#ifndef nmsaService_H
#define nmsaService_H

class StewardLogger;

class NMSA_Service
{
    private:
        StewardLogger *logger;

    public:
        //! Constructor for the NMSA service wrapper
        /*!
         * \param myLogger is the logger instance we should use
         */
        NMSA_Service(StewardLogger *myLogger);

        //! Destructor for the NMSA service wrapper
        ~NMSA_Service();
};

#endif
