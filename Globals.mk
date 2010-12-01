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

INSTALL=install
INSTALL_GID=eil
INSTALL_UID=eil

CFLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses
CP_FLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses

LDFLAGS=
CP_LDFLAGS=-lgsoap++

# Flags for static linking - Be sure to check the README and LICENSE files
# for concerns when static linking!
STATIC_BASE=-static
STATIC_CC=-static-libgcc
STATIC_CPP=-static-libstdc++
