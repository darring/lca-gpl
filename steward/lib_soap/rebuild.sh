#!/usr/bin/env bash

# gSOAP rebuild script

CLEANUP_FILES=$(cat <<EOF
EILClientOps.h
WSHttpBinding_USCOREIEILClientOperations.nsmap
WSHttpBinding_USCOREIEILClientOperations.GetCommandStatus.req.xml
WSHttpBinding_USCOREIEILClientOperations.GetCommandStatus.res.xml
WSHttpBinding_USCOREIEILClientOperations.GetCommandToExecute.req.xml
soapC.cpp
soapC.co
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

TYPEMAP=$(cat <<EOF
base = "http://tempuri.org/"
base_imports = "http://tempuri.org/Imports"
serialization = "http://schemas.microsoft.com/2003/10/Serialization/"
clientManageService = "http://schemas.datacontract.org/2004/07/EILClientManagmentService"
serializationArrays = "http://schemas.microsoft.com/2003/10/Serialization/Arrays"
EOF
)

rm typemap.dat
touch typemap.dat

for LINE in $TYPEMAP
do
    echo "${LINE}" >> typemap.dat
done

#wsdl2h -g -c -s -o EILClientOps.h "http://10.10.0.20/CCMS/EILClientOperationsService.svc?wsdl"

#soapcpp2 -i -C -c -I /usr/include/gsoap/ EILClientOps.h

wsdl2h -g -f -o EILClientOps.h "http://10.10.0.20/CCMS/EILClientOperationsService.svc?wsdl"

soapcpp2 -i -C -I /usr/include/gsoap/ EILClientOps.h

echo "gSOAP files reconstructed"
