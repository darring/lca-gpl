/*
 * sighandlers Header
 */

/*! \mainpage Signal Handler functions for the EIL Linux Client Agent
 *
 * \section intro_sec Introduction
 *
 * This is a collection of signal handler functions for the EIL Linux Client
 * Agent.
 * \section signals_sec Handled Signals
 *
 * The steward interprets the following signals in the following ways:
 *
 *   <table>
 *   <tr>
 *   <td>SIGHUP</td><td>Causes steward to exit gracefully.</td></tr><tr>
 *   <td>SIGINT</td><td>Causes steward to exit gracefully.</td></tr><tr>
 *   <td>SIGTERM</td><td>Causes steward to exit quickly (gracefully if possible)</td>
 *   </tr>
 *   </table>
 *
 */

#ifndef sigHandlers_H
#define sigHandlers_H

//! Call to set up the signal handlers
/*!
 * This function should be called once per application execution to set up the
 * signal handlers. If it is called more than once, it will fail silently.
 */
void setupSignalHandlers();

//! Handle the SIGHUP signal
/*! Should not be called except by sigaction!
 * \param sig The signal
 */
void handle_SIGHUP(int sig);

//! Handle the SIGINT signal
/*! Should not be called except by sigaction!
 * \param sig The signal
 */
void handle_SIGINT(int sig);

//! Handle the SIGTERM signal
/*! Should not be called except by sigaction!
 * \param sig The signal
 */
void handle_SIGTERM(int sig);
#endif
