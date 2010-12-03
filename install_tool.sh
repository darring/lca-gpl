#!/usr/bin/env bash

# Linux Client Agent Installation Tool
#-------------------------------------
# This tool is intended to assist in the installation and packaging of the
# Linux Client Agent

unset OPT_BUILD OPT_STATIC OPT_DOC OPT_PKG OPT_INSTALL_PKG || true
unset OPT_INSTALL_DISPATCHER OPT_INSTALL_STEWARD LOG_FILE || true
unset OPT_CLEAN OPT_UNINSTALL_DISPATCHER OPT_UNINSTALL_STEWARD || true
unset TMP_WORKSPACE TMP_BASE TMP_ROOT || true

PROGNAME=${0##*/}

MY_CWD=`pwd`

if [ "$(id -u)" != "0" ]; then
    echo "This install tool script must be run as root!"
    exit 1
fi

. ./install_helper.sh

usage()
{
    cat <<EOF
Usage: $PROGNAME [OPTION]
Where [OPTION] is one of the following

    --install       Installs the client agent on the system
                    (building as needed)

    --uninstall     Uninstalls the client agent from the system

    --pkginstall    Install the client agent from a package
                    (should not be called unless you know what you are doing)

    --instdisp      Installs just the dispatcher on the system

    --inststew      Installs just the steward on the system

    --uninstdisp    Uninstalls the dispatcher

    --uninststew    Uninstalls the steward

    --build         Build the steward (rebuilding if needed)

    --static        Build the steward with static linking (rebuilding if
                    needed)

    --clean         Clean the steward build environment

    --doc           Install just the documentation

    --pkg           Build an installable package (static linked)

If ran without any options, this usage text will be displayed.
EOF
}

if [ "$1" = "" ]; then
    usage
    exit 0
fi

# Parse command line.
TEMP=$(getopt -n "$PROGNAME" --options h \
--longoptions build,\
install,\
instdisp,\
inststew,\
uninstall,\
uninstdisp,\
uninststew,\
pkginstall,\
static,\
clean,\
doc,\
pkg -- $*)

if [ $? -ne 0 ]; then
    echo "Error while parsing options!"
    usage
    exit 1
fi

eval set -- "$TEMP"

while [ $1 != -- ]; do
    case "$1" in
        --install)
            OPT_INSTALL_DISPATCHER=yes
            OPT_INSTALL_STEWARD=yes
            shift
            ;;
        --uninstall)
            OPT_UNINSTALL_STEWARD=yes
            OPT_UNINSTALL_DISPATCHER=yes
            shift
            ;;
        --instdisp)
            OPT_INSTALL_DISPATCHER=yes
            shift
            ;;
        --uninstdisp)
            OPT_UNINSTALL_DISPATCHER=yes
            shift
            ;;
        --inststew)
            OPT_INSTALL_STEWARD=yes
            shift
            ;;
        --uninststew)
            OPT_UNINSTALL_STEWARD=yes
            shift
            ;;
        --pkginstall)
            OPT_INSTALL_PKG=yes
            shift
            ;;
        --doc)
            OPT_DOC=yes
            shift
            ;;
        --build)
            OPT_BUILD=yes
            shift
            ;;
        --static)
            OPT_STATIC=yes
            shift
            ;;
        --clean)
            OPT_CLEAN=yes
            shift
            ;;
        --pkg)
            OPT_STATIC=yes
            OPT_PKG=yes
            shift
            ;;
        -h)
            usage
            exit 0
            ;;
        *)
            break
            ;;
    esac
done
shift

# Actual install functions
# NOTE: The order of these matter!
# For example, on install, the dispatcher must be installed before the steward
# and on uninstall, the steward must be uninstalled before the dispatcher.

if [ -n "$OPT_BUILD" ]; then
    trace "!!! Rebuilding steward agent"
    set -x
    cd steward/
    make clean
    make
    cd ../
    set +x
fi

if [ -n "$OPT_STATIC" ]; then
    trace "!!! Rebuilding steward agent (static linking)"
    set -x
    cd steward/
    make clean
    make static
    cd ../
    set +x
fi

if [ -n "$OPT_CLEAN" ]; then
    trace "!!! Cleaning steward build environment"
    set -x
    cd steward/
    make clean
    cd ../
    set +x
fi

if [ -n "$OPT_DOC" ]; then
    trace "!!! DOC INSTALLATION NOT IMPLEMENTED YET"
    # TODO
fi

# NOTE: Install before the steward!
if [ -n "$OPT_INSTALL_DISPATCHER" ]; then
    install_dispatcher
fi

# NOTE: Uninstall before the dispatcher!
if [ -n "$OPT_UNINSTALL_STEWARD" ]; then
    trace "!!! Uninstalling the steward"
    set -x
    unlink ${I_USRBIN_DIR}/eil_steward
    unlink ${I_BIN_DIR}/eil_steward
    set +x
fi

if [ -n "$OPT_UNINSTALL_DISPATCHER" ]; then
    trace "!!! Uninstalling the dispatcher"
    cd dispatcher/
    ./install.sh -p
    cd ../
fi

if [ -n "$OPT_INSTALL_STEWARD" ]; then
    install_steward
fi

##############################
####### PACKAGE FUNCTIONS

if [ -n "$OPT_PKG" ]; then
    if [ ! -n "$OPT_STATIC" ]; then
        alert "!!! Well this is embarrassing, somehow you've managed to trigger the"
        alert "!!! 'build package' routines without actually building a static steward,"
        alert "!!! which shouldn't be possible!"
        die "!!! Dying on unrecoverable error!"
    fi
    trace "!!! Building an installable package"
    setup_env
    install_steward
    trace "!!! Bundling up the installer..."
    install -v --mode=754 install_tool.sh install_helper.sh ${TMP_ROOT}
    cp -fvr dispatcher ${TMP_ROOT}
    set -x
    cd ${TMP_BASE}
    tar c eil_clientagent-${EIL_LCA_VERSION} > ${MY_CWD}/eil_clientagent-${EIL_LCA_VERSION}.tar
    gzip ${MY_CWD}/eil_clientagent-${EIL_LCA_VERSION}.tar
    cd ${MY_CWD}
    set +x
    trace "!!! Installable package ready,"
    trace "!!! ${MY_CWD}/eil_clientagent-${EIL_LCA_VERSION}.tar.gz"
    trace "!!! Unarchive the file, and from the package directory run:"
    trace "!!!     $ install_tool.sh --pkginstall"
    cleanup_env
fi
