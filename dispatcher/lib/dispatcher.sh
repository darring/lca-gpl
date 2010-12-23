# Command dispatcher

# INTERNAL RUN COMMAND
# Not intended to be used externally
_run_command() {
    # FIXME Do we want to do any error checking here?
    # Currently fire and forget
    ${BIN_DIR}/elevate_script ${SCRIPTS_DIR}/${PLATFORM_NAME}_${*}
}

# This is the general command processor.
#
# Its job is to take the incoming commands from the client agent
# directory, interpret what they mean, and then dispatch them to the
# various bit players around the Linux box which ultimately perform
# those actions we need done (rebooting, domain join/unjoining, etc.)
process_command() {
    if [ "$*" = "reboot" ]; then
        _run_command "reboot"
    fi
}
