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

/*! If this file is present on the file system (and stat'able by the steward)
 * then it means that the NMSA service can run on this system.
 */
#define NMSA_TOGGLE "/opt/intel/eil/clientagent/home/.nmsa_enable"

#endif
