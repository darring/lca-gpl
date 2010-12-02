#!/usr/bin/env bash

# Linux Client Agent Installation Tool
#-------------------------------------
# This tool is intended to assist in the installation and packaging of the
# Linux Client Agent

unset OPT_BUILD OPT_STATIC OPT_DOC OPT_PKG || true
unset OPT_INSTALL_DISPATCHER OPT_INSTALL_STEWARD || true

PROGNAME=${0##*/}

if [ "$(id -u)" != "0" ]; then
    echo "This install tool script must be run as root!"
    exit 1
fi

usage()
{
    cat <<EOF
Usage: $PROGNAME [OPTION]
Where [OPTION] is one of the following

    --install       Installs the client agent on the system
                    (building as needed)

    --instdisp      Installs just the dispatcher on the system

    --inststew      Installs just the steward on the system

    --build         Build the steward (rebuilding if needed)

    --static        Build the steward with static linking (rebuilding if
                    needed)

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
static,\
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
    echo "!!! Rebuilding steward agent"
    set -x
    cd steward/
    make clean
    make
    cd ../
    set +x
fi

if [ -n "$OPT_STATIC" ]; then
    echo "!!! Rebuilding steward agent (static linking)"
    set -x
    cd steward/
    make clean
    make static
    cd ../
    set +x
fi

if [ -n "$OPT_DOC" ]; then
    echo "!!! DOC INSTALLATION NOT IMPLEMENTED YET"
    # TODO
fi
