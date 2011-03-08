/*
 * nmsaService.h
 */

/*! \mainpage NMSA service wrapper for the EIL Linux Client Agent
 *
 * \section Introduction Introduction
 *
 *  This will be the wrapper for the NMSA service, once we begin to integrate
 * it with the rest of the Linux client agent. However, for now, it is largely
 * just a stub.
 *
 * \section Usage Usage
 *
 * This section will describe the usage.
 *
 * \section other Other subsections
 *
 * \li \subpage assetHelper "Asset Helper"
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
