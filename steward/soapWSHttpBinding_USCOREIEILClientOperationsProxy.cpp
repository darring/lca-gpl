/* soapWSHttpBinding_USCOREIEILClientOperationsProxy.cpp
   Generated by gSOAP 2.7.9l from eil_steward.h
   Copyright(C) 2000-2007, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#include "soapWSHttpBinding_USCOREIEILClientOperationsProxy.h"

WSHttpBinding_USCOREIEILClientOperationsProxy::WSHttpBinding_USCOREIEILClientOperationsProxy()
{	WSHttpBinding_USCOREIEILClientOperationsProxy_init(SOAP_IO_DEFAULT, SOAP_IO_DEFAULT);
}

WSHttpBinding_USCOREIEILClientOperationsProxy::WSHttpBinding_USCOREIEILClientOperationsProxy(soap_mode iomode)
{	WSHttpBinding_USCOREIEILClientOperationsProxy_init(iomode, iomode);
}

WSHttpBinding_USCOREIEILClientOperationsProxy::WSHttpBinding_USCOREIEILClientOperationsProxy(soap_mode imode, soap_mode omode)
{	WSHttpBinding_USCOREIEILClientOperationsProxy_init(imode, omode);
}

void WSHttpBinding_USCOREIEILClientOperationsProxy::WSHttpBinding_USCOREIEILClientOperationsProxy_init(soap_mode imode, soap_mode omode)
{	soap_imode(this, imode);
	soap_omode(this, omode);
	soap_endpoint = NULL;
	static const struct Namespace namespaces[] =
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"ns3", "http://schemas.microsoft.com/2003/10/Serialization/", NULL, NULL},
	{"ns4", "http://schemas.datacontract.org/2004/07/EILClientManagmentService", NULL, NULL},
	{"ns5", "http://schemas.microsoft.com/2003/10/Serialization/Arrays", NULL, NULL},
	{"ns1", "http://tempuri.org/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	if (!this->namespaces)
		this->namespaces = namespaces;
}

WSHttpBinding_USCOREIEILClientOperationsProxy::~WSHttpBinding_USCOREIEILClientOperationsProxy()
{ }

void WSHttpBinding_USCOREIEILClientOperationsProxy::soap_noheader()
{	header = NULL;
}

const SOAP_ENV__Fault *WSHttpBinding_USCOREIEILClientOperationsProxy::soap_fault()
{	return this->fault;
}

const char *WSHttpBinding_USCOREIEILClientOperationsProxy::soap_fault_string()
{	return *soap_faultstring(this);
}

const char *WSHttpBinding_USCOREIEILClientOperationsProxy::soap_fault_detail()
{	return *soap_faultdetail(this);
}

int WSHttpBinding_USCOREIEILClientOperationsProxy::GetCommandToExecute(_ns1__GetCommandToExecute *ns1__GetCommandToExecute, _ns1__GetCommandToExecuteResponse *ns1__GetCommandToExecuteResponse)
{	struct soap *soap = this;
	struct __ns1__GetCommandToExecute soap_tmp___ns1__GetCommandToExecute;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://rmssvr01.eil-infra.com/CCMS/EILClientOperationsService.svc";
	soap_action = "http://tempuri.org/IEILClientOperations/GetCommandToExecute";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetCommandToExecute.ns1__GetCommandToExecute = ns1__GetCommandToExecute;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetCommandToExecute(soap, &soap_tmp___ns1__GetCommandToExecute);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetCommandToExecute(soap, &soap_tmp___ns1__GetCommandToExecute, "-ns1:GetCommandToExecute", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetCommandToExecute(soap, &soap_tmp___ns1__GetCommandToExecute, "-ns1:GetCommandToExecute", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetCommandToExecuteResponse)
		return soap_closesock(soap);
	ns1__GetCommandToExecuteResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetCommandToExecuteResponse->soap_get(soap, "ns1:GetCommandToExecuteResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WSHttpBinding_USCOREIEILClientOperationsProxy::UpdateCommandStatus(_ns1__UpdateCommandStatus *ns1__UpdateCommandStatus, _ns1__UpdateCommandStatusResponse *ns1__UpdateCommandStatusResponse)
{	struct soap *soap = this;
	struct __ns1__UpdateCommandStatus soap_tmp___ns1__UpdateCommandStatus;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://rmssvr01.eil-infra.com/CCMS/EILClientOperationsService.svc";
	soap_action = "http://tempuri.org/IEILClientOperations/UpdateCommandStatus";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__UpdateCommandStatus.ns1__UpdateCommandStatus = ns1__UpdateCommandStatus;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__UpdateCommandStatus(soap, &soap_tmp___ns1__UpdateCommandStatus);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__UpdateCommandStatus(soap, &soap_tmp___ns1__UpdateCommandStatus, "-ns1:UpdateCommandStatus", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__UpdateCommandStatus(soap, &soap_tmp___ns1__UpdateCommandStatus, "-ns1:UpdateCommandStatus", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__UpdateCommandStatusResponse)
		return soap_closesock(soap);
	ns1__UpdateCommandStatusResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__UpdateCommandStatusResponse->soap_get(soap, "ns1:UpdateCommandStatusResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WSHttpBinding_USCOREIEILClientOperationsProxy::GetCommandStatus(_ns1__GetCommandStatus *ns1__GetCommandStatus, _ns1__GetCommandStatusResponse *ns1__GetCommandStatusResponse)
{	struct soap *soap = this;
	struct __ns1__GetCommandStatus soap_tmp___ns1__GetCommandStatus;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://rmssvr01.eil-infra.com/CCMS/EILClientOperationsService.svc";
	soap_action = "http://tempuri.org/IEILClientOperations/GetCommandStatus";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__GetCommandStatus.ns1__GetCommandStatus = ns1__GetCommandStatus;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__GetCommandStatus(soap, &soap_tmp___ns1__GetCommandStatus);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__GetCommandStatus(soap, &soap_tmp___ns1__GetCommandStatus, "-ns1:GetCommandStatus", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__GetCommandStatus(soap, &soap_tmp___ns1__GetCommandStatus, "-ns1:GetCommandStatus", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__GetCommandStatusResponse)
		return soap_closesock(soap);
	ns1__GetCommandStatusResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__GetCommandStatusResponse->soap_get(soap, "ns1:GetCommandStatusResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}

int WSHttpBinding_USCOREIEILClientOperationsProxy::InitiateClientCommands(_ns1__InitiateClientCommands *ns1__InitiateClientCommands, _ns1__InitiateClientCommandsResponse *ns1__InitiateClientCommandsResponse)
{	struct soap *soap = this;
	struct __ns1__InitiateClientCommands soap_tmp___ns1__InitiateClientCommands;
	const char *soap_action = NULL;
	if (!soap_endpoint)
		soap_endpoint = "http://rmssvr01.eil-infra.com/CCMS/EILClientOperationsService.svc";
	soap_action = "http://tempuri.org/IEILClientOperations/InitiateClientCommands";
	soap->encodingStyle = NULL;
	soap_tmp___ns1__InitiateClientCommands.ns1__InitiateClientCommands = ns1__InitiateClientCommands;
	soap_begin(soap);
	soap_serializeheader(soap);
	soap_serialize___ns1__InitiateClientCommands(soap, &soap_tmp___ns1__InitiateClientCommands);
	if (soap_begin_count(soap))
		return soap->error;
	if (soap->mode & SOAP_IO_LENGTH)
	{	if (soap_envelope_begin_out(soap)
		 || soap_putheader(soap)
		 || soap_body_begin_out(soap)
		 || soap_put___ns1__InitiateClientCommands(soap, &soap_tmp___ns1__InitiateClientCommands, "-ns1:InitiateClientCommands", "")
		 || soap_body_end_out(soap)
		 || soap_envelope_end_out(soap))
			 return soap->error;
	}
	if (soap_end_count(soap))
		return soap->error;
	if (soap_connect(soap, soap_endpoint, soap_action)
	 || soap_envelope_begin_out(soap)
	 || soap_putheader(soap)
	 || soap_body_begin_out(soap)
	 || soap_put___ns1__InitiateClientCommands(soap, &soap_tmp___ns1__InitiateClientCommands, "-ns1:InitiateClientCommands", "")
	 || soap_body_end_out(soap)
	 || soap_envelope_end_out(soap)
	 || soap_end_send(soap))
		return soap_closesock(soap);
	if (!ns1__InitiateClientCommandsResponse)
		return soap_closesock(soap);
	ns1__InitiateClientCommandsResponse->soap_default(soap);
	if (soap_begin_recv(soap)
	 || soap_envelope_begin_in(soap)
	 || soap_recv_header(soap)
	 || soap_body_begin_in(soap))
		return soap_closesock(soap);
	ns1__InitiateClientCommandsResponse->soap_get(soap, "ns1:InitiateClientCommandsResponse", "");
	if (soap->error)
	{	if (soap->error == SOAP_TAG_MISMATCH && soap->level == 2)
			return soap_recv_fault(soap);
		return soap_closesock(soap);
	}
	if (soap_body_end_in(soap)
	 || soap_envelope_end_in(soap)
	 || soap_end_recv(soap))
		return soap_closesock(soap);
	return soap_closesock(soap);
}
/* End of client proxy code */
