#ifndef commands_H
#define commands_H

//! The return state of a command issuance (whether request or execution)
enum CCMS_ReturnState
{
    COMMAND_SUCCESS,
    COMMAND_ERROR,
    COMMAND_TCP_ERROR,
    COMMAND_ERROR_STATE,
};

//! The specific command issued
enum CCMS_CommandIssued
{
    NO_COMMAND,
    REBOOT,
    TCP_DIAGNOSE,
    AGENT_UPDATE,
    ASSET_REFRESH,
};

//! The command structure issued from CCMS
struct CCMS_Command
{
    //! The return state
    CCMS_ReturnState ReturnState;
    //! The actuall command issued
    CCMS_CommandIssued Command;
};

//! The command status returned from the dispatcher
struct Dispatcher_Command_Status
{
    //! Success or faliure
    bool Success;

    // NOTE making this a struct now in case we need to grow it down the road
};

#endif

