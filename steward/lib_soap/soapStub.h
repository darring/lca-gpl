/* soapStub.h
   Generated by gSOAP 2.7.9l from EILClientOps.h
   Copyright(C) 2000-2007, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************\
 *                                                                            *
 * Enumerations                                                               *
 *                                                                            *
\******************************************************************************/


#ifndef SOAP_TYPE_xsd__boolean
#define SOAP_TYPE_xsd__boolean (13)
/* xsd:boolean */
enum xsd__boolean {xsd__boolean__false_ = 0, xsd__boolean__true_ = 1};
#endif

#ifndef SOAP_TYPE_ns4__MachineType
#define SOAP_TYPE_ns4__MachineType (19)
/* ns4:MachineType */
enum ns4__MachineType {ns4__MachineType__ANY = 0, ns4__MachineType__HOST_USCOREWILDCARD = 1, ns4__MachineType__HOST = 2, ns4__MachineType__FQDN = 3, ns4__MachineType__UUID = 4, ns4__MachineType__COLLECTION = 5};
#endif

#ifndef SOAP_TYPE_ns4__EILCommandStatus
#define SOAP_TYPE_ns4__EILCommandStatus (20)
/* ns4:EILCommandStatus */
enum ns4__EILCommandStatus {ns4__EILCommandStatus__COMMAND_USCOREISSUED = 0, ns4__EILCommandStatus__COMMAND_USCORERECEIVED = 1, ns4__EILCommandStatus__COMMAND_USCOREEXECUTION_USCORESTARTED = 2, ns4__EILCommandStatus__COMMAND_USCOREEXECUTION_USCORECOMPLETE = 3, ns4__EILCommandStatus__COMMAND_USCOREFAILED = 4, ns4__EILCommandStatus__WAIT_USCOREFOR_USCOREMANUAL_USCORESTEP = 5, ns4__EILCommandStatus__COMMAND_USCORETIMED_USCOREOUT = 6, ns4__EILCommandStatus__COMMAND_USCOREDELAYED_USCORERESPONSE = 7, ns4__EILCommandStatus__COMMAND_USCORERETRY = 8};
#endif

/******************************************************************************\
 *                                                                            *
 * Classes and Structs                                                        *
 *                                                                            *
\******************************************************************************/


#ifndef SOAP_TYPE_xsd__base64Binary
#define SOAP_TYPE_xsd__base64Binary (9)
/* Base64 schema type: */
struct xsd__base64Binary
{
	unsigned char *__ptr;
	int __size;
	char *id;	/* optional element of type xsd:string */
	char *type;	/* optional element of type xsd:string */
	char *options;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE__ns1__GetCommandToExecute
#define SOAP_TYPE__ns1__GetCommandToExecute (21)
/* ns1:GetCommandToExecute */
struct _ns1__GetCommandToExecute
{
	struct ns4__MachineContext *ctx;	/* optional element of type ns4:MachineContext */
};
#endif

#ifndef SOAP_TYPE__ns1__GetCommandToExecuteResponse
#define SOAP_TYPE__ns1__GetCommandToExecuteResponse (24)
/* ns1:GetCommandToExecuteResponse */
struct _ns1__GetCommandToExecuteResponse
{
	struct ns4__EILCommand *GetCommandToExecuteResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns4:EILCommand */
};
#endif

#ifndef SOAP_TYPE__ns1__UpdateCommandStatus
#define SOAP_TYPE__ns1__UpdateCommandStatus (27)
/* ns1:UpdateCommandStatus */
struct _ns1__UpdateCommandStatus
{
	struct ns4__MachineContext *ctx;	/* optional element of type ns4:MachineContext */
	struct ns4__EILCommand *cmd;	/* optional element of type ns4:EILCommand */
};
#endif

#ifndef SOAP_TYPE__ns1__UpdateCommandStatusResponse
#define SOAP_TYPE__ns1__UpdateCommandStatusResponse (28)
/* ns1:UpdateCommandStatusResponse */
struct _ns1__UpdateCommandStatusResponse
{
	enum xsd__boolean *UpdateCommandStatusResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:boolean */
};
#endif

#ifndef SOAP_TYPE__ns1__GetCommandStatus
#define SOAP_TYPE__ns1__GetCommandStatus (30)
/* ns1:GetCommandStatus */
struct _ns1__GetCommandStatus
{
	struct ns4__MachineContext *ctx;	/* optional element of type ns4:MachineContext */
};
#endif

#ifndef SOAP_TYPE__ns1__GetCommandStatusResponse
#define SOAP_TYPE__ns1__GetCommandStatusResponse (31)
/* ns1:GetCommandStatusResponse */
struct _ns1__GetCommandStatusResponse
{
	struct ns4__MachineContext *GetCommandStatusResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type ns4:MachineContext */
};
#endif

#ifndef SOAP_TYPE__ns1__InitiateClientCommands
#define SOAP_TYPE__ns1__InitiateClientCommands (32)
/* ns1:InitiateClientCommands */
struct _ns1__InitiateClientCommands
{
	struct ns4__MachineContext *ctx;	/* optional element of type ns4:MachineContext */
	struct ns4__EILCommand *cmd;	/* optional element of type ns4:EILCommand */
	char *ownrID;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE__ns1__InitiateClientCommandsResponse
#define SOAP_TYPE__ns1__InitiateClientCommandsResponse (33)
/* ns1:InitiateClientCommandsResponse */
struct _ns1__InitiateClientCommandsResponse
{
	char *InitiateClientCommandsResult;	/* SOAP 1.2 RPC return element (when namespace qualified) */	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns4__MachineContext
#define SOAP_TYPE_ns4__MachineContext (22)
/* ns4:MachineContext */
struct ns4__MachineContext
{
	struct ns5__ArrayOfstring *mContext;	/* optional element of type ns5:ArrayOfstring */
	struct ns5__ArrayOfstring *mList;	/* optional element of type ns5:ArrayOfstring */
	struct ns5__ArrayOfKeyValueOfstringstring *mParams;	/* optional element of type ns5:ArrayOfKeyValueOfstringstring */
	enum ns4__MachineType *mType;	/* optional element of type ns4:MachineType */
};
#endif

#ifndef SOAP_TYPE_ns4__EILCommand
#define SOAP_TYPE_ns4__EILCommand (25)
/* ns4:EILCommand */
struct ns4__EILCommand
{
	char *CommandExitMessage;	/* optional element of type xsd:string */
	char *CommandName;	/* optional element of type xsd:string */
	struct ns5__ArrayOfKeyValueOfstringstring *CommandParameters;	/* optional element of type ns5:ArrayOfKeyValueOfstringstring */
	char *CommandPath;	/* optional element of type xsd:string */
	char *CommandResult;	/* optional element of type xsd:string */
	enum ns4__EILCommandStatus *CommandStatus;	/* optional element of type ns4:EILCommandStatus */
	enum xsd__boolean *CommandSuccessful;	/* optional element of type xsd:boolean */
	int *ErrorCode;	/* optional element of type xsd:int */
	int *ExpectedTimeOut;	/* optional element of type xsd:int */
	char *OperationID;	/* optional element of type xsd:string */
	char *SetMachineType;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns5__ArrayOfstring
#define SOAP_TYPE_ns5__ArrayOfstring (34)
/* ns5:ArrayOfstring */
struct ns5__ArrayOfstring
{
	int __sizestring;	/* sequence of elements <string> */
	char **string;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE__ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring
#define SOAP_TYPE__ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring (42)
/* ns5:ArrayOfKeyValueOfstringstring-KeyValueOfstringstring */
struct _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring
{
	char *Key;	/* optional element of type xsd:string */
	char *Value;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_ns5__ArrayOfKeyValueOfstringstring
#define SOAP_TYPE_ns5__ArrayOfKeyValueOfstringstring (36)
/* ns5:ArrayOfKeyValueOfstringstring */
struct ns5__ArrayOfKeyValueOfstringstring
{
	int __sizeKeyValueOfstringstring;	/* sequence of elements <KeyValueOfstringstring> */
	struct _ns5__ArrayOfKeyValueOfstringstring_KeyValueOfstringstring *KeyValueOfstringstring;	/* optional element of type ns5:ArrayOfKeyValueOfstringstring-KeyValueOfstringstring */
};
#endif

#ifndef SOAP_TYPE___ns1__GetCommandToExecute
#define SOAP_TYPE___ns1__GetCommandToExecute (84)
/* Operation wrapper: */
struct __ns1__GetCommandToExecute
{
	struct _ns1__GetCommandToExecute *ns1__GetCommandToExecute;	/* optional element of type ns1:GetCommandToExecute */
};
#endif

#ifndef SOAP_TYPE___ns1__UpdateCommandStatus
#define SOAP_TYPE___ns1__UpdateCommandStatus (88)
/* Operation wrapper: */
struct __ns1__UpdateCommandStatus
{
	struct _ns1__UpdateCommandStatus *ns1__UpdateCommandStatus;	/* optional element of type ns1:UpdateCommandStatus */
};
#endif

#ifndef SOAP_TYPE___ns1__GetCommandStatus
#define SOAP_TYPE___ns1__GetCommandStatus (92)
/* Operation wrapper: */
struct __ns1__GetCommandStatus
{
	struct _ns1__GetCommandStatus *ns1__GetCommandStatus;	/* optional element of type ns1:GetCommandStatus */
};
#endif

#ifndef SOAP_TYPE___ns1__InitiateClientCommands
#define SOAP_TYPE___ns1__InitiateClientCommands (96)
/* Operation wrapper: */
struct __ns1__InitiateClientCommands
{
	struct _ns1__InitiateClientCommands *ns1__InitiateClientCommands;	/* optional element of type ns1:InitiateClientCommands */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (97)
/* SOAP Header: */
struct SOAP_ENV__Header
{
#ifdef WITH_NOEMPTYSTRUCT
	char dummy;	/* dummy member to enable compilation */
#endif
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (98)
/* SOAP Fault Code: */
struct SOAP_ENV__Code
{
	char *SOAP_ENV__Value;	/* optional element of type xsd:QName */
	struct SOAP_ENV__Code *SOAP_ENV__Subcode;	/* optional element of type SOAP-ENV:Code */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (100)
/* SOAP-ENV:Detail */
struct SOAP_ENV__Detail
{
	int __type;	/* any type of element <fault> (defined below) */
	void *fault;	/* transient */
	char *__any;
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (103)
/* SOAP-ENV:Reason */
struct SOAP_ENV__Reason
{
	char *SOAP_ENV__Text;	/* optional element of type xsd:string */
};
#endif

#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (104)
/* SOAP Fault: */
struct SOAP_ENV__Fault
{
	char *faultcode;	/* optional element of type xsd:QName */
	char *faultstring;	/* optional element of type xsd:string */
	char *faultactor;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *detail;	/* optional element of type SOAP-ENV:Detail */
	struct SOAP_ENV__Code *SOAP_ENV__Code;	/* optional element of type SOAP-ENV:Code */
	struct SOAP_ENV__Reason *SOAP_ENV__Reason;	/* optional element of type SOAP-ENV:Reason */
	char *SOAP_ENV__Node;	/* optional element of type xsd:string */
	char *SOAP_ENV__Role;	/* optional element of type xsd:string */
	struct SOAP_ENV__Detail *SOAP_ENV__Detail;	/* optional element of type SOAP-ENV:Detail */
};
#endif

/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/

#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (4)
typedef char *_XML;
#endif

#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (5)
typedef char *_QName;
#endif

#ifndef SOAP_TYPE_xsd__ID
#define SOAP_TYPE_xsd__ID (6)
typedef char *xsd__ID;
#endif

#ifndef SOAP_TYPE_xsd__IDREF
#define SOAP_TYPE_xsd__IDREF (7)
typedef char *xsd__IDREF;
#endif

#ifndef SOAP_TYPE_xsd__anyURI
#define SOAP_TYPE_xsd__anyURI (8)
typedef char *xsd__anyURI;
#endif

#ifndef SOAP_TYPE_xsd__decimal
#define SOAP_TYPE_xsd__decimal (14)
typedef char *xsd__decimal;
#endif

#ifndef SOAP_TYPE_xsd__duration
#define SOAP_TYPE_xsd__duration (15)
typedef char *xsd__duration;
#endif

#ifndef SOAP_TYPE_ns3__char
#define SOAP_TYPE_ns3__char (16)
typedef int ns3__char;
#endif

#ifndef SOAP_TYPE_ns3__duration
#define SOAP_TYPE_ns3__duration (17)
typedef char *ns3__duration;
#endif

#ifndef SOAP_TYPE_ns3__guid
#define SOAP_TYPE_ns3__guid (18)
typedef char *ns3__guid;
#endif

#ifndef SOAP_TYPE__ns3__anyType
#define SOAP_TYPE__ns3__anyType (44)
typedef char *_ns3__anyType;
#endif

#ifndef SOAP_TYPE__ns3__anyURI
#define SOAP_TYPE__ns3__anyURI (45)
typedef char *_ns3__anyURI;
#endif

#ifndef SOAP_TYPE__ns3__base64Binary
#define SOAP_TYPE__ns3__base64Binary (46)
typedef struct xsd__base64Binary _ns3__base64Binary;
#endif

#ifndef SOAP_TYPE__ns3__boolean
#define SOAP_TYPE__ns3__boolean (47)
typedef enum xsd__boolean _ns3__boolean;
#endif

#ifndef SOAP_TYPE__ns3__byte
#define SOAP_TYPE__ns3__byte (48)
typedef char _ns3__byte;
#endif

#ifndef SOAP_TYPE__ns3__dateTime
#define SOAP_TYPE__ns3__dateTime (50)
typedef time_t _ns3__dateTime;
#endif

#ifndef SOAP_TYPE__ns3__decimal
#define SOAP_TYPE__ns3__decimal (51)
typedef char *_ns3__decimal;
#endif

#ifndef SOAP_TYPE__ns3__double
#define SOAP_TYPE__ns3__double (53)
typedef double _ns3__double;
#endif

#ifndef SOAP_TYPE__ns3__float
#define SOAP_TYPE__ns3__float (55)
typedef float _ns3__float;
#endif

#ifndef SOAP_TYPE__ns3__int
#define SOAP_TYPE__ns3__int (56)
typedef int _ns3__int;
#endif

#ifndef SOAP_TYPE__ns3__long
#define SOAP_TYPE__ns3__long (58)
typedef LONG64 _ns3__long;
#endif

#ifndef SOAP_TYPE__ns3__QName
#define SOAP_TYPE__ns3__QName (59)
typedef char *_ns3__QName;
#endif

#ifndef SOAP_TYPE__ns3__short
#define SOAP_TYPE__ns3__short (61)
typedef short _ns3__short;
#endif

#ifndef SOAP_TYPE__ns3__string
#define SOAP_TYPE__ns3__string (62)
typedef char *_ns3__string;
#endif

#ifndef SOAP_TYPE__ns3__unsignedByte
#define SOAP_TYPE__ns3__unsignedByte (63)
typedef unsigned char _ns3__unsignedByte;
#endif

#ifndef SOAP_TYPE__ns3__unsignedInt
#define SOAP_TYPE__ns3__unsignedInt (64)
typedef unsigned int _ns3__unsignedInt;
#endif

#ifndef SOAP_TYPE__ns3__unsignedLong
#define SOAP_TYPE__ns3__unsignedLong (66)
typedef ULONG64 _ns3__unsignedLong;
#endif

#ifndef SOAP_TYPE__ns3__unsignedShort
#define SOAP_TYPE__ns3__unsignedShort (68)
typedef unsigned short _ns3__unsignedShort;
#endif

#ifndef SOAP_TYPE__ns3__char
#define SOAP_TYPE__ns3__char (69)
typedef int _ns3__char;
#endif

#ifndef SOAP_TYPE__ns3__duration
#define SOAP_TYPE__ns3__duration (70)
typedef char *_ns3__duration;
#endif

#ifndef SOAP_TYPE__ns3__guid
#define SOAP_TYPE__ns3__guid (71)
typedef char *_ns3__guid;
#endif

#ifndef SOAP_TYPE__ns3__FactoryType
#define SOAP_TYPE__ns3__FactoryType (72)
typedef char *_ns3__FactoryType;
#endif

#ifndef SOAP_TYPE__ns3__Id
#define SOAP_TYPE__ns3__Id (73)
typedef char *_ns3__Id;
#endif

#ifndef SOAP_TYPE__ns3__Ref
#define SOAP_TYPE__ns3__Ref (74)
typedef char *_ns3__Ref;
#endif

#ifndef SOAP_TYPE__ns4__MachineContext
#define SOAP_TYPE__ns4__MachineContext (75)
typedef struct ns4__MachineContext _ns4__MachineContext;
#endif

#ifndef SOAP_TYPE__ns4__MachineType
#define SOAP_TYPE__ns4__MachineType (76)
typedef enum ns4__MachineType _ns4__MachineType;
#endif

#ifndef SOAP_TYPE__ns4__EILCommand
#define SOAP_TYPE__ns4__EILCommand (77)
typedef struct ns4__EILCommand _ns4__EILCommand;
#endif

#ifndef SOAP_TYPE__ns4__EILCommandStatus
#define SOAP_TYPE__ns4__EILCommandStatus (78)
typedef enum ns4__EILCommandStatus _ns4__EILCommandStatus;
#endif

#ifndef SOAP_TYPE__ns5__ArrayOfstring
#define SOAP_TYPE__ns5__ArrayOfstring (79)
typedef struct ns5__ArrayOfstring _ns5__ArrayOfstring;
#endif

#ifndef SOAP_TYPE__ns5__ArrayOfKeyValueOfstringstring
#define SOAP_TYPE__ns5__ArrayOfKeyValueOfstringstring (80)
typedef struct ns5__ArrayOfKeyValueOfstringstring _ns5__ArrayOfKeyValueOfstringstring;
#endif


/******************************************************************************\
 *                                                                            *
 * Typedef Synonyms                                                           *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


#ifdef __cplusplus
}
#endif

#endif

/* End of soapStub.h */
