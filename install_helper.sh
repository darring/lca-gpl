# This scriptlet is not intended to be run by itself, it merely provides
# helper functionality to the install_tool

# Convenience defintions for the various bash color prompts
COLOR_RESET='\e[0m'
COLOR_TRACE='\e[0;34m' # Blue
COLOR_WARNING='\e[1;33m' # Yellow
COLOR_ALERT='\e[4;31m' # Underline red

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