#ifndef EIL_defines_H
#define EIL_defines_H

/*
 * Various defines used by the steward service
 *
 * You can think of these as constants
 */

#ifndef WSA5__ADDRESS_ANONYMOUS
#define WSA5__ADDRESS_ANONYMOUS "http://www.w3.org/2005/08/addressing/anonymous"
#endif

#ifndef EIL__CLIENTOPSERVICE
#define EIL__CLIENTOPSERVICE "http://CCMS_SERVER/CCMS/EILClientOperationsService.svc"
#endif

#ifndef EIL__GETCOMMANDTOEXECUTE
#define EIL__GETCOMMANDTOEXECUTE "http://tempuri.org/IEILClientOperations/GetCommandToExecute"
#endif

#ifndef EIL__GETCOMMANDTOEXECUTEUSINGMACADDRESS
#define EIL__GETCOMMANDTOEXECUTEUSINGMACADDRESS "http://tempuri.org/IEILClientOperations/GetCommandToExecuteUsingMacAddress"
#endif

#ifndef EIL__UPDATECOMMANDSTATUS
#define EIL__UPDATECOMMANDSTATUS "http://tempuri.org/IEILClientOperations/UpdateCommandStatus"
#endif

#endif
