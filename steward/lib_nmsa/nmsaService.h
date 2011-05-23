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

        //! Register with the NMSA
        /*!
         * TODO - Currently stubbed. However, the stub definition is taken from
         * the document "NMSA - Client Interaction Documentation.doc" dated
         * March 28th 2011, which defines the interface as:
         * \li client_register.php?mac=a&hostname=b&bmc=c&bridge=d&trans=e
         *
         * \param hwAddr The hardware address
         * \param hostname The hostname
         * \param bmc IP Address of the BMC
         * \param bridge IP Address of the BMC bridge address
         * \param trans IP Address of the BMC transport address
         *
         * \remarks logOutput will have to be freed somewhere! TODO
          */
        void register(char *hwAddr, char *hostname, char *bmc, char *bridge, char *trans);

    public:
        //! Constructor for the NMSA service wrapper
        /*!
         * \param myLogger is the logger instance we should use
         */
        NMSA_Service(StewardLogger *myLogger);

        //! Destructor for the NMSA service wrapper
        ~NMSA_Service();

        //! Poll the NMSA
        /*!
         * TODO - Currently stubbed. However, the stub definition is taken from
         * the document "NMSA - Client Interaction Documentation.doc" dated
         * Jan 25th 2011, which defines the interface as:
         * \li client_poll.php?mac=x&hostname=y
         *
         * \param hwAddr The hardware address
         * \param hostname The hostname
         */
        void Poll(char *hwAddr, char *hostname);
};

#endif
