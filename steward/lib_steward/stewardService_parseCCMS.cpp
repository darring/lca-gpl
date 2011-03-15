/*
 * Parsing of the CCMS commands
 */

#include "logger.h"
#include "stewardService.h"
#include "EIL_defines.h"
#include "CCMS_commands.h"

int StewardService::parseCommandFromCCMS(
            ns4__MachineContext *ctx,
            ns4__EILCommand *EILCommand,
            CCMS_Command *returnCommand)
{
    /*
    Be sure to update the header with the proper HTTP SOAP
    action! (or else we will get an "ActionMismatch" error)
    */
    header.wsa5__Action = EIL__UPDATECOMMANDSTATUS;
    synHeaders();

    /*
    First we need to get our responses ready
    */
    _ns1__UpdateCommandStatus updateCmdStat;
    ns4__EILCommand cmd;
    _ns1__UpdateCommandStatusResponse updateCmdStatResp;

    updateCmdStat.ctx = ctx;

    // Parse *what* our command was
    if(strcasecmp(
        EILCommand->CommandName, CCMS_REBOOT)
        == 0)
    {
        currentState = STATE_ExecutingCommand;
        returnCommand->ReturnState = COMMAND_SUCCESS;
        returnCommand->Command = REBOOT;

        ns4__EILCommandStatus complete =
            ns4__EILCommandStatus__COMMAND_USCOREEXECUTION_USCORECOMPLETE;
        int errorcode = 0;
        cmd.CommandResult = RESPONSE_REBOOT;
        cmd.CommandStatus = &complete;
        cmd.ErrorCode = &errorcode;
        cmd.CommandName =
            EILCommand->CommandName;

        updateCmdStat.cmd = &cmd;
        updateCmdStat.cmd->OperationID =
            EILCommand->OperationID;

        return service.UpdateCommandStatus(
            &updateCmdStat, &updateCmdStatResp);
    } else if(strcasecmp(
        EILCommand->CommandName, CCMS_ASSETREFRESH)
        == 0)
    {
        currentState = STATE_None; // We can't be stuck in exec state here
        returnCommand->ReturnState = COMMAND_SUCCESS;
        returnCommand->Command = ASSET_REFRESH;

        ns4__EILCommandStatus complete =
            ns4__EILCommandStatus__COMMAND_USCOREEXECUTION_USCORECOMPLETE;
        int errorcode = 0;
        cmd.CommandResult = RESPONSE_ASSETREFRESH;
        cmd.CommandStatus = &complete;
        cmd.ErrorCode = &errorcode;
        cmd.CommandName =
            EILCommand->CommandName;

        updateCmdStat.cmd = &cmd;
        updateCmdStat.cmd->OperationID =
            EILCommand->OperationID;

        return service.UpdateCommandStatus(
            &updateCmdStat, &updateCmdStatResp);
    } else if(strcasecmp(
        EILCommand->CommandName, CCMS_UPDATE)
        == 0)
    {
        currentState = STATE_ExecutingCommand;
        returnCommand->ReturnState = COMMAND_SUCCESS;
        returnCommand->Command = AGENT_UPDATE;

        ns4__EILCommandStatus complete =
            ns4__EILCommandStatus__COMMAND_USCOREEXECUTION_USCORECOMPLETE;
        int errorcode = 0;
        cmd.CommandResult = RESPONSE_UPDATE;
        cmd.CommandStatus = &complete;
        cmd.ErrorCode = &errorcode;
        cmd.CommandName =
            EILCommand->CommandName;

        updateCmdStat.cmd = &cmd;
        updateCmdStat.cmd->OperationID =
            EILCommand->OperationID;

        return service.UpdateCommandStatus(
            &updateCmdStat, &updateCmdStatResp);
    } // Other commands go here
    else
    {
        currentState = STATE_None;
        returnCommand->ReturnState = COMMAND_ERROR;
        returnCommand->Command = NO_COMMAND;
    }
    return SOAP_OK;
}
