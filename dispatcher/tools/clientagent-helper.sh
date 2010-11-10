#!/usr/bin/env bash

# Client Agent Helper Script
#----------------------------
# This tool is a helper script intended to bridge the gap between the
# dispatcher and the steward. It fills in the steward with specific
# information that the dispatcher will know about.
#
# The main advantage of storing this information in the dispatcher is
# that changing it involves updating simple bash scripts and will not
# require a recompile of the steward agent.

PROGNAME=${0##*/}

# Set up the installation directories

# We use /opt for our installation location to adhere to LSB Linux
# Filesystem Hierarchy Standards (this gives us maximum compatibility
# across the various distros we aim to support).
BASE_DIR=/opt

# Intel has a registered provider name with the LSB
LANANA=$BASE_DIR/intel

# We want to have our own sub-directory under that specific to the
# EIL namespace, additionally, we want our client agent to live there.
INSTALL_DIR=$LANANA/eil/clientagent

BIN_DIR=$INSTALL_DIR/bin
LIB_DIR=$INSTALL_DIR/lib
DOC_DIR=$INSTALL_DIR/doc
TOOL_DIR=$INSTALL_DIR/tools
HOME_DIR=$INSTALL_DIR/home
SCRIPTS_DIR=$INSTALL_DIR/scripts

. ${LIB_DIR}/globals.sh

usage()
{
    cat <<EOF
Usage: $PROGNAME [OPTION]
Where [OPTION] is one of the following

    --base          Returns the base directory used by client agent

    --install       Returns the base install directory used by client
                    agent

    --bin           Returns the binary directory used by client agent

    --lib           Returns the library directory used by client agent

    --doc           Returns the documentation directory used by client
                    agent

    --tool          Returns the tools directory used by client agent

    --home          Returns the home directory used by client agent

    --scripts       Returns the scripts directory used by client agent

    --comdir        Returns the command directory used by client agent

    --uid           Returns the UID used by client agent

    --gid           Returns the GID used by client agent

    --stdlog        Returns the path to the standard log used by client
                    agent

    --ccmslog       Returns the path to the CCMS log used by client agent

    --errlog        Returns the path to the error log used by client agent

If ran without any options, this usage text will be displayed.
EOF
}

# Parse command line.
TEMP=$(getopt -n "$PROGNAME" \
--longoptions base,\
install,\
bin,\
lib,\
doc,\
tool,\
home,\
scripts,\
comdir,\
uid,\
gid,\
stdlog,\
ccmslog,\
errlog -- $*)

if [ $? -ne 0 ]; then
    usage
    die "Error while parsing options"
fi

eval set -- "$TEMP"

while [ $1 != -- ]; do
    case "$1" in
        ## Directory options
        --base)
            echo "${BASE_DIR}"
            shift
            ;;
        --install)
            echo "${INSTALL_DIR}"
            shift
            ;;
        --bin)
            echo "${BIN_DIR}"
            shift
            ;;
        --lib)
            echo "${LIB_DIR}"
            shift
            ;;
        --doc)
            echo "${DOC_DIR}"
            shift
            ;;
        --tool)
            echo "${TOOL_DIR}"
            shift
            ;;
        --home)
            echo "${HOME_DIR}"
            shift
            ;;
        --scripts)
            echo "${SCRIPTS_DIR}"
            shift
            ;;
        --comdir)
            echo "${COMMAND_DIR}"
            shift
            ;;
        ## UID/GID options
        --uid)
            echo "${UID}"
            shift
            ;;
        --gid)
            echo "${GID}"
            shift
            ;;
        ## Log options
        --stdlog)
            echo "${STANDARD_LOG_FILE}"
            shift
            ;;
        --ccmslog)
            echo "${CCMS_LOG_FILE}"
            shift
            ;;
        --errlog)
            echo "${ERROR_LOG_FILE}"
            shift
            ;;
        *)
            break
            ;;
    esac
done
shift
