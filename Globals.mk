# Global makefile settings

# Set this empty to disable debugging (when ready for release)
DEBUG=-g

# gSOAP includes
GSOAP_INCLUDES=-I/usr/local/share/gsoap/plugin/
GSOAP_SOURCES=/usr/local/share/gsoap/plugin/wsaapi.c
GSOAP_WSAAPI_O=wsaapi.o
GSOAP_OBJECTS=$(GSOAP_WSAAPI_O)

# FIXME - Add defines for reducing gSOAP build size by removing the server
# code as it wont be needed

CC=gcc
CPP=g++

CFLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses
CP_FLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses

LDFLAGS=
CP_LDFLAGS=-lgsoap++

