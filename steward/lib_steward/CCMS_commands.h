/*
 * CCMS_commands.h
 */

/*! \page ccms_commands CCMS Command Defines
 *
 * \section intro_sec Introduction
 *
 * This file provides the defines for the upstream CCMS commands.
 *
 * CCMS_commands.h
 */

#ifndef CCMS_commands_h
#define CCMS_commands_h

//! The reboot command
#define CCMS_REBOOT "reboot"

//! The auto-update command - FIXME - Need this command from Madhu- Sam
#define CCMS_UPDATE "update"

//! The command to refresh and update the asset information
#define CCMS_ASSETREFRESH "get asset info"

//! The reboot response to CCMS
#define RESPONSE_REBOOT "Reboot Successful"

//! The asset refresh response to CCMS - FIXME - Need this from Madhu- Sam
#define RESPONSE_ASSETREFRESH "Asset refresh successful"

//! The update response to CCMS - FIXME - Need this from Madhu- Sam
#define RESPONSE_UPDATE "Update successful"

#endif
