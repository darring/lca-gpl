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

    #ifdef CCMS_LOCAL_SERVER
    #define EIL__CLIENTOPSERVICE "http://127.0.0.1/CCMS/EILClientOperationsService.svc"
    #elif defined(CCMS_DEV_SERVER)
    #define EIL__CLIENTOPSERVICE "http://172.16.3.12/CCMS/EILClientOperationsService.svc"
    #else // Default is CCMS_PRO_SERVER (production)
    #define EIL__CLIENTOPSERVICE "http://172.16.3.10/CCMS/EILClientOperationsService.svc"
    #endif

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

#ifndef EIL__UPDATEASSETINFO
#define EIL__UPDATEASSETINFO "http://tempuri.org/IEILClientOperations/UpdateAssetInformation"
#endif

#endif
