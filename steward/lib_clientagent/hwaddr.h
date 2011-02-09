/*
 * Hardware Address tools header
 */

/*! \mainpage Hardware Address Tools
 *
 * \section intro_sec Introduction
 *
 * This file provides interfaces which abstract access to the hardware address
 * for the EIL Linux client agent.
 *
 * \section usage_sec Usage
 *
 */

#ifndef hwaddr_h
#define hwaddr_h

//! Obtains the lowest order hardware address
/*!
 * When called, will attempt to run through the potential network interfaces
 * on the system and return a string for the hardware address of the lowest
 * order interface.
 *
 * \param hwaddr The char pointer for the hardware address string
 */
void getHwAddr(char *hwaddr);

#endif
