#!/usr/bin/env bash

CCMS_SERVER=172.16.3.10
#CCMS_SERVER=172.16.3.12

# gSOAP rebuild script

CLEANUP_FILES=$(cat <<EOF
EILClientOps.h
WSHttpBinding_USCOREIEILClientOperations.nsmap
WSHttpBinding_USCOREIEILClientOperations.GetCommandStatus.req.xml
WSHttpBinding_USCOREIEILClientOperations.GetCommandStatus.res.xml
WSHttpBinding_USCOREIEILClientOperations.GetCommandToExecute.req.xml
soapC.cpp
soapC.c
WSHttpBinding_USCOREIEILClientOperations.GetCommandToExecute.res.xml
soapH.h
WSHttpBinding_USCOREIEILClientOperations.InitiateClientCommands.req.xml
soapStub.h
WSHttpBinding_USCOREIEILClientOperations.InitiateClientCommands.res.xml
soapWSHttpBinding_USCOREIEILClientOperationsProxy.cpp
WSHttpBinding_USCOREIEILClientOperations.UpdateCommandStatus.req.xml
soapWSHttpBinding_USCOREIEILClientOperationsProxy.h
WSHttpBinding_USCOREIEILClientOperations.UpdateCommandStatus.res.xml
EOF
)

for THIS_FILE in $CLEANUP_FILES
do
    # Yeah, I'm being paranoid
    rm -i $THIS_FILE
done

wsdl2h -g -s -f -o EILClientOps.h "http://${CCMS_SERVER}/CCMS/EILClientOperationsService.svc?wsdl"

cat header_append.h >> EILClientOps.h

soapcpp2 -a -i -C -I/usr/local/share/gsoap/import EILClientOps.h

echo "gSOAP files reconstructed"
