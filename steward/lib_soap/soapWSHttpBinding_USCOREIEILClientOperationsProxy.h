/* soapWSHttpBinding_USCOREIEILClientOperationsProxy.h
   Generated by gSOAP 2.7.9l from EILClientOps.h
   Copyright(C) 2000-2007, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapWSHttpBinding_USCOREIEILClientOperationsProxy_H
#define soapWSHttpBinding_USCOREIEILClientOperationsProxy_H
#include "soapH.h"

class SOAP_CMAC WSHttpBinding_USCOREIEILClientOperationsProxy : public soap
{ public:
	/// Endpoint URL of service 'WSHttpBinding_USCOREIEILClientOperationsProxy' (change as needed)
	const char *soap_endpoint;
	/// Constructor
	WSHttpBinding_USCOREIEILClientOperationsProxy();
	/// Constructor with engine input+output mode control
	WSHttpBinding_USCOREIEILClientOperationsProxy(soap_mode iomode);
	/// Constructor with engine input and output mode control
	WSHttpBinding_USCOREIEILClientOperationsProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~WSHttpBinding_USCOREIEILClientOperationsProxy();
	/// Initializer used by constructor
	virtual	void WSHttpBinding_USCOREIEILClientOperationsProxy_init(soap_mode imode, soap_mode omode);
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Put SOAP Header in message
	virtual	void soap_header(char *t__Action, char *t__MessageID, char *t__To);
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Web service operation 'GetCommandToExecute' (return error code or SOAP_OK)
	virtual	int GetCommandToExecute(_ns1__GetCommandToExecute *ns1__GetCommandToExecute, _ns1__GetCommandToExecuteResponse *ns1__GetCommandToExecuteResponse);
	/// Web service operation 'UpdateCommandStatus' (return error code or SOAP_OK)
	virtual	int UpdateCommandStatus(_ns1__UpdateCommandStatus *ns1__UpdateCommandStatus, _ns1__UpdateCommandStatusResponse *ns1__UpdateCommandStatusResponse);
	/// Web service operation 'GetCommandStatus' (return error code or SOAP_OK)
	virtual	int GetCommandStatus(_ns1__GetCommandStatus *ns1__GetCommandStatus, _ns1__GetCommandStatusResponse *ns1__GetCommandStatusResponse);
	/// Web service operation 'InitiateClientCommands' (return error code or SOAP_OK)
	virtual	int InitiateClientCommands(_ns1__InitiateClientCommands *ns1__InitiateClientCommands, _ns1__InitiateClientCommandsResponse *ns1__InitiateClientCommandsResponse);
};
#endif
