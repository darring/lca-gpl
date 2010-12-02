# This scriptlet is not intended to be run by itself, it merely provides
# helper functionality to the install_tool

###########################################################
# Convenience defintions for the various bash color prompts
###########################################################
COLOR_RESET='\e[0m'
COLOR_TRACE='\e[0;34m' # Blue
COLOR_WARNING='\e[1;33m' # Yellow
COLOR_ALERT='\e[4;31m' # Underline red

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
I_LANANA=$BASE_DIR/intel

# We want to have our own sub-directory under that specific to the
# EIL namespace, additionally, we want our client agent to live there.
I_INSTALL_DIR=$LANANA/eil/clientagent

I_BIN_DIR=$I_INSTALL_DIR/bin
I_LIB_DIR=$I_INSTALL_DIR/lib
I_DOC_DIR=$I_INSTALL_DIR/doc
I_TOOL_DIR=$I_INSTALL_DIR/tools
I_HOME_DIR=$I_INSTALL_DIR/home
I_SCRIPTS_DIR=$I_INSTALL_DIR/scripts

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
        echo -e "$*" >> ${LOG_FILE}
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