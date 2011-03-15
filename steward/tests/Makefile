# Makefile for the steward unit tests

include ../../Globals.mk

LOGGER_H=../logger/logger.h ../logger/err_defines.h
LOGGER_CPP=../logger/logger.cpp
LOGGER_ALL=$(LOGGER_CPP) $(LOGGER_H)

ASSETHELPER_H=../lib_nmsa/assetHelper.h
ASSETHELPER_CPP=../lib_nmsa/assetHelper.cpp
ASSETHELPER_ALL=$(ASSETHELPER_CPP) $(ASSETHELPER_H)

INCLUDES_LOGGER=-I../logger/
INCLUDES_ASSETHELPER=-I../lib_nmsa/

all: assetHelper_test

assetHelper_test: logger.o assetHelper.o assetHelper_test.o
	$(CPP) logger.o assetHelper.o assetHelper_test.o -o assetHelper_test

logger.o: assetHelper_test.o

assetHelper.o: assetHelper_test.o

assetHelper_test.o: assetHelper_test.cpp $(LOGGER_ALL) $(ASSETHELPER_ALL)
	$(CPP) $(CP_FLAGS) $(INCLUDES_LOGGER) $(INCLUDES_ASSETHELPER) \
		assetHelper_test.cpp $(LOGGER_CPP) $(ASSETHELPER_CPP)

.PHONY: clean

clean:
	@echo Cleaning the test build environment
	@rm -f *~ *.o *.so core core.*
	@rm -f assetHelper_test
