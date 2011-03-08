# Makefile for the EIL Linux client agent steward

include ../Globals.mk

SOURCES=eil_steward.cpp lib_soap/soapC.cpp \
	logger/logger.cpp lib_steward/stewardService_parseOp.cpp \
	lib_steward/stewardService.cpp lib_nmsa/assetHelper.cpp \
	lib_hash/uniqueHash.cpp lib_clientagent/clientagent_helper.cpp \
	lib_dispatcher/dispatcher_helper.cpp lib_clientagent/hwaddr.cpp \
	lib_nmsa/nmsaService.cpp \
	lib_soap/soapWSHttpBinding_USCOREIEILClientOperationsProxy.cpp \

HEADERS=logger/logger.h lib_soap/soapH.h lib_steward/stewardService.h \
	lib_hash/uniqueHash.h lib_clientagent/clientagent_helper.h \
	lib_dispatcher/dispatcher_helper.h lib_clientagent/hwaddr.h \
	lib_nmsa/nmsaService.h lib_steward/CCMS_commands.h \
	lib_nmsa/assetHelper.h \
	lib_soap/soapWSHttpBinding_USCOREIEILClientOperationsProxy.h \
	lib_soap/WSHttpBinding_USCOREIEILClientOperations.nsmap

OBJECTS=logger.o soapC.o uniqueHash.o stewardService.o hwaddr.o \
	stewardService_parseOp.o assetHelper.o \
	clientagent_helper.o dispatcher_helper.o nmsaService.o \
	soapWSHttpBinding_USCOREIEILClientOperationsProxy.o \
	eil_steward.o

INCLUDES=-I./logger/ -I./lib_soap/ -I./lib_steward/ -I./lib_hash/ \
	 -I./lib_clientagent/ -I./lib_nmsa/ -I./sig_handlers/ \
	 -I./lib_dispatcher/

eil_steward: $(OBJECTS)
	$(CPP) $(GSOAP_OBJECTS) $(OBJECTS) $(CP_LDFLAGS) -o eil_steward

static: $(OBJECTS)
	@echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	@echo Static linking enabled - Be sure to check the README/INSTALL
	@echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	$(CPP) $(STATIC_BASE) $(STATIC_CC) \
		$(GSOAP_OBJECTS) $(OBJECTS) $(CP_LDFLAGS) -o eil_steward

assetHelper.o: eil_steward.o

hwaddr.o: eil_steward.o

logger.o: eil_steward.o

soapC.o: eil_steward.o

stewardService_parseOp.o: eil_steward.o

stewardService.o: eil_steward.o

uniqueHash.o: eil_steward.o

clientagent_helper.o: eil_steward.o

dispatcher_helper.o: eil_steward.o

nmsaService.o: eil_steward.o

GSOAP_WSAAPI_O: eil_steward.o

eil_steward.o: $(SOURCES) $(HEADERS)
	$(CPP) $(CP_FLAGS) $(INCLUDES) $(GSOAP_INCLUDES) $(GSOAP_SOURCES) $(SOURCES)

.PHONY: clean

clean:
	@echo Cleaning the build environment
	@rm -f *~ *.o *.so core core.* lib_hash/*~ lib_clientagent/*~
	@rm -f ../*~ ../dispatcher/*~ ../dispatcher/lib/*~ ../dispatcher/bin/*~
	@rm -f ../dispatcher/scripts/*~ ../dispatcher/tests/*~ ../dispatcher/tools/*~
	@rm -f logger/*~ logger/*.o logger/*.so logger/core logger/core.*
	@rm -f lib_soap/*~ lib_soap/*.o lib_soap/*.so lib_soap/core lib_soap/core.*
	@rm -f lib_steward/*~ lib_steward/*.o lib_steward/core lib_steward/core.*
	@rm -f lib_dispatcher/*~ lib_nmsa/*~
	@rm -f eil_steward
