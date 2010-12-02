#!/usr/bin/env bash

# Linux Client Agent Installation Tool
#-------------------------------------
# This tool is intended to assist in the installation and packaging of the
# Linux Client Agent

unset OPT_BUILD OPT_STATIC OPT_DOC OPT_PKG OPT_INSTALL_PKG || true
unset OPT_INSTALL_DISPATCHER OPT_INSTALL_STEWARD LOG_FILE || true
unset OPT_CLEAN || true

PROGNAME=${0##*/}

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

    --pkginstall    Install the client agent from a package
                    (should not be called unless you know what you are doing)

    --instdisp      Installs just the dispatcher on the system

    --inststew      Installs just the steward on the system

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
        ## Directory options
        --install)
            OPT_INSTALL_DISPATCHER=yes
            OPT_INSTALL_STEWARD=yes
            shift
            ;;
        --instdisp)
            OPT_INSTALL_DISPATCHER=yes
            shift
            ;;
        --inststew)
            OPT_INSTALL_STEWARD=yes
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

if [ -n "$OPT_INSTALL_DISPATCHER" ]; then
    trace "!!! Installing the dispatcher"
    cd dispatcher/
    ./install.sh
    cd ../
fi

if [ -n "$OPT_INSTALL_STEWARD" ]; then
    trace "!!! Installing the steward"
    warning "!!! WARNING: This step requires the dispatcher to have been installed previously!"
    if [ -z "$OPT_STATIC" && -z "$OPT_BUILD" ]; then
        warning "!!! WARNING: The steward had not been built, so we will build it with dynamic linking"
        set -x
        cd steward/
        make clean
        make
        cd ../
        set +x
    fi
    set -x

    set +x
fi
