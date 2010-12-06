
#ifndef stewardState_H
#define stewardState_H

enum ServiceState
{
    STATE_None
};

enum StewardState
{
    S_STATE_Null,
    S_STATE_Running,
    S_STATE_Shutdown,
    S_STATE_Terminate
};

//! The current steward system state
static StewardState S_STATE;

#endif
