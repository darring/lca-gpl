# Makefile for the EIL Linux client agent steward

include ../Globals.mk

SOURCES=eil_steward.cpp logger/logger.cpp lib_soap/soapC.cpp \
	lib_soap/soapWSHttpBinding_USCOREIEILClientOperationsProxy.cpp

HEADERS=logger/logger.h lib_soap/soapH.h \
	lib_soap/soapWSHttpBinding_USCOREIEILClientOperationsProxy.h \
	lib_soap/WSHttpBinding_USCOREIEILClientOperations.nsmap

OBJECTS=logger.o soapC.o \
	soapWSHttpBinding_USCOREIEILClientOperationsProxy.o \
	eil_steward.o

INCLUDES=-I./logger/ -I./lib_soap/

eil_steward: $(OBJECTS)
	$(CPP) $(OBJECTS) $(CP_LDFLAGS) -o eil_steward

logger.o: eil_steward.o

soapC.o: eil_steward.o

eil_steward.o: $(SOURCES) $(HEADERS)
	$(CPP) $(CP_FLAGS) $(INCLUDES) $(SOURCES)

clean:
	@echo Cleaning the build environment
	@rm -f *~ *.o *.so core core.*
	@rm -f logger/*~ logger/*.o logger/*.so logger/core logger/core.*
	@rm -f lib_soap/*~ lib_soap/*.o lib_soap/*.so lib_soap/core lib_soap/core.*
	@rm -f eil_steward
