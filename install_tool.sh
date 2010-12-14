#!/usr/bin/env sh

# Linux Client Agent Installation Tool
#-------------------------------------
# This tool is intended to assist in the installation and packaging of the
# Linux Client Agent

unset OPT_BUILD OPT_STATIC OPT_DOC OPT_PKG OPT_INSTALL_PKG || true
unset OPT_INSTALL_DISPATCHER OPT_INSTALL_STEWARD LOG_FILE || true
unset OPT_CLEAN OPT_UNINSTALL_DISPATCHER OPT_UNINSTALL_STEWARD || true
unset TMP_WORKSPACE TMP_BASE TMP_ROOT IS_RELEASE OPT_MAKEREPO || true
unset REMOTE_REPO || true

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

    --makerepo      Build installable package and make a repo.
                    Requires an additional option specifying the IP address
                    and path we should use for the repo. E.g.:
                    --makerepo SOMESERVER:/home/pub/releases/.

------------------------------------------------------------------------------

   The following helper options can be added to --pkginstall or --pkg

    -r              The installable package is a release package.
                    This means that the installable package will be named
                    generically if called with --pkg and that the output will
                    go to a log file in /var/log if called with --pkginstall.

If ran without any options, this usage text will be displayed.
EOF
}

if [ "$1" = "" ]; then
    usage
    exit 0
fi

# Parse command line.
TEMP=$(getopt -n "$PROGNAME" --options hr \
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
makerepo:,\
pkg -- $*)

if [ $? -ne 0 ]; then
    echo "Error while parsing options!"
    usage
    exit 1
fi

eval set -- "$TEMP"

while [ $1 != -- ]; do
    case "$1" in
        -r)
            IS_RELEASE=yes
            shift
            ;;
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
        --makerepo)
            OPT_STATIC=yes
            OPT_PKG=yes
            OPT_MAKEREPO=yes
            IS_RELEASE=yes
            if [ -n "$2" ]; then
                REMOTE_REPO="$2"
                shift 2
            else
                die "--makerepo requires an argument"
            fi
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
    install -v --mode=754 install_tool.sh ${TMP_ROOT}
    install -v --mode=644 install_helper.sh ${TMP_ROOT}
    cp -fvr dispatcher ${TMP_ROOT}
    cp VERSION ${TMP_ROOT}/.pkg_version
    cp VERSION ${TMP_ROOT}/.
    if [ -n "$IS_RELEASE" ]; then
        PKG_NAME=eil_clientagent-release
    else
        PKG_NAME=eil_clientagent-${EIL_LCA_VERSION}
    fi
    set -x
    cd ${TMP_BASE}
    tar c ${PKG_NAME} > ${MY_CWD}/${PKG_NAME}.tar
    gzip ${MY_CWD}/${PKG_NAME}.tar
    cd ${MY_CWD}
    set +x
    trace "!!! Installable package ready,"
    trace "!!! ${MY_CWD}/${PKG_NAME}.tar.gz"
    trace "!!! Unarchive the file, and from the package directory run:"
    trace "!!!     $ install_tool.sh --pkginstall"
    cleanup_env
fi

if [ -n "$OPT_INSTALL_PKG" ]; then
    LOG_FILE="/var/log/eil_clientagent_install.log"
    if [ -e ".pkg_version" ]; then
        install_dispatcher
        install_steward
        # We have a chicken/egg kind of problem here-
        # The dispatcher provides items that the steward requires for install,
        # but the steward must be installed before the init script can be ran
        # (and the init script is installed during the dispatcher segment).
        # As a result, we just start the steward service afterward just to be
        # safe.
        /etc/init.d/eil_steward.sh start
    else
        alert "!!! Atempt to install package without a package available!"
        die "!!! Build a package, and try again."
    fi
fi

if [ -n "$OPT_MAKEREPO" ]; then
    trace "!!! Making a repository..."
    set -x
    TMP_REPO=`mktemp -d`
    cd ${MY_CWD}
    cp -f ${MY_CWD}/${PKG_NAME}.tar.gz ${TMP_REPO}/${PKG_NAME}.tar.gz
    cp -f ${MY_CWD}/dispatcher/tools/clientagent-bootstrap.sh ${TMP_REPO}/.
    cp -f ${MY_CWD}/VERSION ${TMP_REPO}/.
    scp ${TMP_REPO}/* ${REMOTE_REPO}
    rm -fr ${TMP_REPO}
    set +x
fi

# vim:set ai et sts=4 sw=4 tw=80:
