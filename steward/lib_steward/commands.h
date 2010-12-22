#ifndef commands_H
#define commands_H

//! The return state of a command issuance (whether request or execution)
enum CCMS_ReturnState
{
    COMMAND_SUCCESS,
    COMMAND_ERROR,
    COMMAND_ERROR_STATE,
};

//! The specific command issued
enum CCMS_CommandIssued
{
    NO_COMMAND,
    REBOOT,
};

struct CCMS_Command
{
    CCMS_ReturnState ReturnState;
    CCMS_CommandIssued Command;
};

#endif