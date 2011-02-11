# Global makefile settings

# Our debugging levels.
# Each level determines how extreme we make our debugging as we are developing.

# DEBUG0 - This can be considered the "release" level. It disables all
#          debugging.
DEBUG0=

# DEBUG1 - This is the standard level, useful for general development. All we
#          enable here is gdb runtime options
DEBUG1=-g

# DEBUG2 - This is switches the daemon to a pure-command-line runnable program.
#          All logging will go to STDOUT, and the process will not fork.
DEBUG2=$(DEBUG1) -D EIL_DEBUG

# Set the DEBUG variable to the level which we want
DEBUG=$(DEBUG1)

EIL_VERSION=$(shell cat ../VERSION)
EIL_VERSION_TEXT=Version $(EIL_VERSION)
EIL_VERSION_DEF=-D 'EIL_VERSION_TEXT="$(EIL_VERSION_TEXT)"'

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

CFLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses $(EIL_VERSION_DEF)
CP_FLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses $(EIL_VERSION_DEF)

LDFLAGS=
CP_LDFLAGS=-lgsoap++

# Flags for static linking - Be sure to check the README and LICENSE files
# for concerns when static linking!
STATIC_BASE=-static
STATIC_CC=-static-libgcc
STATIC_CPP=-static-libstdc++
