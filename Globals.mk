# Global makefile settings

# Set this empty to disable debugging (when ready for release)
DEBUG=-g

CC=gcc
CPP=g++

CFLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses
CP_FLAGS=-c $(DEBUG) -Wall -Wno-write-strings -Wno-parentheses

LDFLAGS=
CP_LDFLAGS=-lgsoap++

