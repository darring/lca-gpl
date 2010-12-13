# This scriptlet is not intended to be run by itself, it merely provides
# helper functionality to the install_tool

####################
# Define the version
####################

EIL_LCA_VERSION=`cat VERSION`

###########################################################
# Convenience defintions for the various bash color prompts
###########################################################
COLOR_RESET='\e[0m'
COLOR_TRACE='\e[0;34m' # Blue
COLOR_WARNING='\e[1;33m' # Yellow
COLOR_ALERT='\e[4;31m' # Underline red
COLOR_DIE='\e[30m\033[41m' # Red background, black text

#####################################
# Set up the installation directories
#####################################
# NOTE: These are actually intended to be in a different namespace than the
# rest of the client agent scripts. The reason for this is that we wish to
# isolate the install process from the runtime process. Thus, all of our
# directory variables have the I_ prefix.

# We use /opt for our installation location to adhere to LSB Linux
# Filesystem Hierarchy Standards (this gives us maximum compatibility
# across the various distros we aim to support).
I_BASE_DIR=/opt

# Intel has a registered provider name with the LSB
I_LANANA=$I_BASE_DIR/intel

# We want to have our own sub-directory under that specific to the
# EIL namespace, additionally, we want our client agent to live there.
I_INSTALL_DIR=$I_LANANA/eil/clientagent

I_BIN_DIR=/bin
I_LIB_DIR=/lib
I_DOC_DIR=/doc
I_TOOL_DIR=/tools
I_HOME_DIR=/home
I_SCRIPTS_DIR=/scripts

# Location of the symbolic links
I_USRBIN_DIR=/usr/bin

#####################
# UID/GID definitions
#####################

I_INSTALL_UID="eil"
I_INSTALL_GID="eil"

#################
# Trace functions
#################
inner_trace () {
    if [ -n "$LOG_FILE" ]; then
        echo -e "$(date) $*" >> ${LOG_FILE}
    else
        echo -e "$*"
    fi
}

warning () {
    if [ -n "$LOG_FILE" ]; then
        inner_trace "$*"
    else
        inner_trace "${COLOR_WARNING}$*${COLOR_RESET}"
    fi
}

trace () {
    if [ -n "$LOG_FILE" ]; then
        inner_trace "$*"
    else
        inner_trace "${COLOR_TRACE}$*${COLOR_RESET}"
    fi
}

alert() {
    if [ -n "$LOG_FILE" ]; then
        inner_trace "$*"
    else
        inner_trace "${COLOR_ALERT}$*${COLOR_RESET}"
    fi
}

die() {
    if [ -n "$LOG_FILE" ]; then
        inner_trace "$*"
    else
        inner_trace "${COLOR_DIE}$*${COLOR_RESET}"
    fi
    cleanup_env
    exit 1
}

#################################
# Various sundry helper functions
#################################

check_uid_gid() {
    egrep -i "^$I_INSTALL_GID" /etc/group > /dev/null
    if [ $? -ne 0 ]; then
        # Group does not exist
        alert "!!! Group does not exist, check that dispatcher has been installed!"
        die "!!! Cannot proceed!"
    fi

    egrep -i "^$I_INSTALL_UID" /etc/passwd > /dev/null
    if [ $? -ne 0 ]; then
        # User does not exist
        alert "!!! User does not exist, check that dispatcher has been installed!"
        die "!!! Cannot proceed!"
    fi

}

setup_env() {
    if [ -n "$TMP_WORKSPACE" ]; then
        # That's odd, well, let's just clean it up then!
        cleanup_env
    else
        TMP_BASE=`mktemp -d`
        if [ -n "$IS_RELEASE" ]; then
            TMP_ROOT="${TMP_BASE}/eil_clientagent-release"
        else
            TMP_ROOT="${TMP_BASE}/eil_clientagent-${EIL_LCA_VERSION}"
        fi
        TMP_WORKSPACE="${TMP_ROOT}/steward"
        mkdir -p $TMP_WORKSPACE
    fi
}

cleanup_env() {
    if [ -n "$TMP_WORKSPACE" ]; then
        rm -fr $TMP_BASE
    fi
}

# Replacement function that provides the same functionality as the install(1)
# command (which is not present on ESXi)
# Usage:
# install_replacement group owner mode file path
install_replacement() {
    local _GROUP=$1
    local _OWNER=$2
    local _MODE=$3
    local _FILE=$4
    local _PATH=$5

    cp -fv $_FILE $_PATH
    chown -v ${_OWNER}:${_GROUP} ${_PATH}/${_FILE}
    chmod -v ${_MODE} ${_PATH}/${_FILE}
}

########################
# Installation functions
########################

install_steward() {
    PREFIX_PATH="${I_INSTALL_DIR}${I_BIN_DIR}"
    if [ -n "$TMP_WORKSPACE" ]; then
        PREFIX_PATH="${TMP_WORKSPACE}"
    fi
    trace "!!! Installing the steward"
    warning "!!! WARNING: This step requires the dispatcher to have been installed previously!"
    check_uid_gid
    if [ -z "$OPT_STATIC" ] && [ -z "$OPT_BUILD" ] && [ ! -e "steward/eil_steward" ]; then
        warning "!!! WARNING: The steward had not been built, so we will build it with dynamic linking"
        set -x
        cd steward/
        make clean
        make
        cd ../
        set +x
    fi
    set -x

    install_replacement "${I_INSTALL_GID}" "${I_INSTALL_UID}" "754" \
        "steward/eil_steward" "${PREFIX_PATH}"

    # SETUID/SETGID
    chmod u+s ${PREFIX_PATH}/eil_steward
    chmod g+s ${PREFIX_PATH}/eil_steward

    if [ ! -n "$TMP_WORKSPACE" ]; then
        ln -s ${PREFIX_PATH}/eil_steward ${I_USRBIN_DIR}/eil_steward
    fi
    set +x
}

install_dispatcher() {
    trace "!!! Installing the dispatcher"
    cd dispatcher/
    if [ -n "$TMP_WORKSPACE" ]; then
        export BOOTSTRAP_DIR="${TMP_WORKSPACE}"
    fi
    ./install.sh
    cd ../
}

# vim:set ai et sts=4 sw=4 tw=80:
