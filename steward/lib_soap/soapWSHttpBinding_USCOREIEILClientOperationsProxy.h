/* soapWSHttpBinding_USCOREIEILClientOperationsProxy.h
   Generated by gSOAP 2.8.0 from EILClientOps.h
   Copyright(C) 2000-2010, Robert van Engelen, Genivia Inc. All Rights Reserved.
   The generated code is released under one of the following licenses:
   GPL OR Genivia's license for commercial use.
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
	/// Constructor with copy of another engine state
	WSHttpBinding_USCOREIEILClientOperationsProxy(const struct soap&);
	/// Constructor with engine input+output mode control
	WSHttpBinding_USCOREIEILClientOperationsProxy(soap_mode iomode);
	/// Constructor with engine input and output mode control
	WSHttpBinding_USCOREIEILClientOperationsProxy(soap_mode imode, soap_mode omode);
	/// Destructor frees deserialized data
	virtual	~WSHttpBinding_USCOREIEILClientOperationsProxy();
	/// Initializer used by constructors
	virtual	void WSHttpBinding_USCOREIEILClientOperationsProxy_init(soap_mode imode, soap_mode omode);
	/// Delete all deserialized data (uses soap_destroy and soap_end)
	virtual	void destroy();
	/// Disables and removes SOAP Header from message
	virtual	void soap_noheader();
	/// Put SOAP Header in message
	virtual	void soap_header(char *wsa5__MessageID, struct wsa5__RelatesToType *wsa5__RelatesTo, struct wsa5__EndpointReferenceType *wsa5__From, struct wsa5__EndpointReferenceType *wsa5__ReplyTo, struct wsa5__EndpointReferenceType *wsa5__FaultTo, char *wsa5__To, char *wsa5__Action);
	/// Get SOAP Header structure (NULL when absent)
	virtual	const SOAP_ENV__Header *soap_header();
	/// Get SOAP Fault structure (NULL when absent)
	virtual	const SOAP_ENV__Fault *soap_fault();
	/// Get SOAP Fault string (NULL when absent)
	virtual	const char *soap_fault_string();
	/// Get SOAP Fault detail as string (NULL when absent)
	virtual	const char *soap_fault_detail();
	/// Force close connection (normally automatic, except for send_X ops)
	virtual	int soap_close_socket();
	/// Print fault
	virtual	void soap_print_fault(FILE*);
#ifndef WITH_LEAN
	/// Print fault to stream
	virtual	void soap_stream_fault(std::ostream&);
	/// Put fault into buffer
	virtual	char *soap_sprint_fault(char *buf, size_t len);
#endif

	/// Web service operation 'GetCommandToExecute' (returns error code or SOAP_OK)
	virtual	int GetCommandToExecute(_ns1__GetCommandToExecute *ns1__GetCommandToExecute, _ns1__GetCommandToExecuteResponse *ns1__GetCommandToExecuteResponse);

	/// Web service operation 'GetCommandToExecuteUsingMacAddress' (returns error code or SOAP_OK)
	virtual	int GetCommandToExecuteUsingMacAddress(_ns1__GetCommandToExecuteUsingMacAddress *ns1__GetCommandToExecuteUsingMacAddress, _ns1__GetCommandToExecuteUsingMacAddressResponse *ns1__GetCommandToExecuteUsingMacAddressResponse);

	/// Web service operation 'UpdateCommandStatus' (returns error code or SOAP_OK)
	virtual	int UpdateCommandStatus(_ns1__UpdateCommandStatus *ns1__UpdateCommandStatus, _ns1__UpdateCommandStatusResponse *ns1__UpdateCommandStatusResponse);

	/// Web service operation 'InitiateClientCommands' (returns error code or SOAP_OK)
	virtual	int InitiateClientCommands(_ns1__InitiateClientCommands *ns1__InitiateClientCommands, _ns1__InitiateClientCommandsResponse *ns1__InitiateClientCommandsResponse);

	/// Web service operation 'InitiateClientCommandsUsingMac' (returns error code or SOAP_OK)
	virtual	int InitiateClientCommandsUsingMac(_ns1__InitiateClientCommandsUsingMac *ns1__InitiateClientCommandsUsingMac, _ns1__InitiateClientCommandsUsingMacResponse *ns1__InitiateClientCommandsUsingMacResponse);

	/// Web service operation 'GetRDPConnectionString' (returns error code or SOAP_OK)
	virtual	int GetRDPConnectionString(_ns1__GetRDPConnectionString *ns1__GetRDPConnectionString, _ns1__GetRDPConnectionStringResponse *ns1__GetRDPConnectionStringResponse);

	/// Web service operation 'InitiateRDPRequest' (returns error code or SOAP_OK)
	virtual	int InitiateRDPRequest(_ns1__InitiateRDPRequest *ns1__InitiateRDPRequest, _ns1__InitiateRDPRequestResponse *ns1__InitiateRDPRequestResponse);

	/// Web service operation 'UpdateAssetInformation' (returns error code or SOAP_OK)
	virtual	int UpdateAssetInformation(_ns1__UpdateAssetInformation *ns1__UpdateAssetInformation, _ns1__UpdateAssetInformationResponse *ns1__UpdateAssetInformationResponse);
};
#endif
