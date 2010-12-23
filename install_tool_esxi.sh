#!/usr/bin/env sh

# Linux Client Agent Installation Tool (ESXi variant)
#----------------------------------------------------
# This tool is intended to assist in the installation and packaging of the
# Linux Client Agent
#
# Unfortunately, we need a specific variant for ESXi, as there doesn't seem to
# be a way to make both ESXi and the other major distros happy at the same time
# with the main install tool.

MY_CWD=`pwd`

if [ "$(id -u)" != "0" ]; then
    echo "This install tool script must be run as root!"
    exit 1
fi

. ./install_helper.sh

if [ ! -e "/bin/bash" ] && [ -f "/.emptytgz" ]; then
    LOG_FILE="/var/log/eil_clientagent_install.log"
    if [ -e ".pkg_version" ]; then
        install_dispatcher
        install_steward
        install_elevate
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
else
    echo "!!! This script must be run on an ESXi system, but this doesn't appear"
    echo "!!! to be an ESXi system"
    cleanup_env
    exit 1
fi

# vim:set ai et sts=4 sw=4 tw=80:
