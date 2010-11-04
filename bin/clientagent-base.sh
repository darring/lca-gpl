#!/bin/sh

# Client agent base (Bash prototype)
# ----------------------------------
# This base takes commands that have already been parsed by another
# application and executes them based up certain criteria. It is
# intended to be fairly lean and require a minimal amount of external
# dependencies (e.g., it should run on a wide variety of platforms with
# minimal additional dependency installation)
#
# Please see the associated INSTALL and README files for more
# information

unset DEBUG || true

# We use /opt for our installation location to adhere to LSB Linux
# Filesystem Hierarchy Standards (this gives us maximum compatibility
# across the various distros we aim to support).
BASE_DIR=/opt

# Intel has a registered provider name with the LSB
LANANA=$BASE_DIR/intel

# We want to have our own sub-directory under that specific to the
# EIL namespace, additionally, we want our client agent to live there.
INSTALL_DIR=$LANANA/eil/clientagent

EXEC=clientagent-base.sh

BIN_DIR=$INSTALL_DIR/bin
LIB_DIR=$INSTALL_DIR/lib
DOC_DIR=$INSTALL_DIR/doc
TOOL_DIR=$INSTALL_DIR/tools
HOME_DIR=$INSTALL_DIR/home

# Load our libraries
. $LIB_DIR/helper.sh
. $LIB_DIR/globals.sh

# Set up our temp files and interfaces
if [ "$TMP_DIR" = "" ]; then
    TMP_DIR="/tmp/clientagent."
    TMP_DIR=${TMP_DIR}$(date +%j%H%M%S)
fi

# vim:set ai et sts=4 sw=4 tw=80:
