####### This is the input file for automake, which will generate Makefile.in ##########
## not a GNU package. You can remove this line, if
## you have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 1.4

noinst_PROGRAMS = wssedemo
SOAPHEADER = wssedemo.h

include ../Makefile.defines
include ../Makefile.c_rules
SOAP_NS = wssedemo.nsmap wssedemo.wsdl

wssedemo_CFLAGS = -DWITH_DOM -DWITH_OPENSSL -DWITH_GZIP
wssedemo_SOURCES = wssedemo.c $(SOAPHEADER) $(SOAP_C_SRC) ../../stdsoap2.c ../../dom.c ../../plugin/wsseapi.c ../../plugin/smdevp.c
wssedemo_LDADD = $(SAMPLE_EXTRA_LIBS) -lssl -lcrypto -lz


