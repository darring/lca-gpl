#!/bin/sh

# The eil_steward init script
# ---------------------------
# The aim of this script is to be as platform agnostic as possible

PATH="${PATH}:/sbin"

. /lib/lsb/init-functions

check_steward_running() {
    if [ -e "/opt/intel/eil/clientagent/home/client-agent.pid" ]; then
        # Verify that it's already running
        local PID1=$(cat /opt/intel/eil/clientagent/home/client-agent.pid)
        if [ -d "/proc/${PID1}" ]; then
            # It's running
            return 0
        else
            # It's not running, we have a dangling PID file
            return 1
        fi
    else
        # It's not running
        return 3
    fi
}

case "$1" in
start)
    # Start the steward service
    check_steward_running
    local _STATUS=$?
    if [ "${_STATUS}" -eq "0" ]; then
        # According to the LSB, this is considered a success
        log_warning_msg "eil_steward already running!"
        log_warning_msg "If you think this is a mistake, check the pid file and"
        log_warning_msg "associated process..."
    elif [ "${_STATUS}" -eq "1" ]; then
        # Service is not running, but pid file exists, let's kill old file
        # and restart
        unlink /opt/intel/eil/clientagent/home/client-agent.pid
        eil_steward
    else
        # Okay to start
        eil_steward
    fi

    exit 0
    ;;
stop)
    # Stop the steward service
    check_steward_running
    local _STATUS=$?
    if [ "${_STATUS}" -eq "0" ]; then
        # Send it SIGHUP
        local PID1=$(cat /opt/intel/eil/clientagent/home/client-agent.pid)
        kill -1 ${PID1}
    elif [ "${_STATUS}" -eq "1" ]; then
        # Service is not running, but pid file exists
        unlink /opt/intel/eil/clientagent/home/client-agent.pid
    else
        log_warning_msg "eil_steward is not running."
    fi
    ;;
retstart|try-restart|reload|force-reload)
    # Restart the steward service
    ;;
status)
    # Display status
    ;;
*)
    # Display usage options
    ;;
esac

