#!/bin/sh

# The client agent bootstrap script
#----------------------------------
# This script is intended to bootstrap the EIL Linux Client Agent
#
# This script must be completely self-contained (unfortunately)

# EIL IP configs
EIL_AUTO="172.16.3.10"
EIL_STAGING="10.4.0.26"

PROGNAME=${0##*/}
MY_CWD=`pwd`
THIS_SCRIPT="${MY_CWD}/${PROGNAME}"

# This function cleans the previous hosts file
clean_hosts_file() {
    local TMP_FILE=`mktemp`
    sed '/## EIL_BEGIN/,/## EIL_END/d' /etc/hosts > ${TMP_FILE}
    cp -f ${TMP_FILE} /etc/hosts
    rm -f ${TMP_FILE}
}

# This function makes the hosts file, it backs up the old hosts file, and
# stores checksum signatures to check for tampering
make_hosts_file() {
    local DATE_STAMP=$(date +%j%H%M%S)
    cp -f /etc/hosts /etc/hosts.backup.${DATE_STAMP}
    md5sum /etc/hosts.backup.${DATE_STAMP} > /etc/hosts.backup.md5.${DATE_STAMP}

    clean_hosts_file

    echo "## EIL_BEGIN" >> /etc/hosts
    echo "### EIL Linux Client Agent Specific Config ###" >> /etc/hosts
    echo "# Changes to this section will be overwritten during client agent upgrades" >> /etc/hosts
    echo "${EIL_AUTO}    eilauto01   eilauto01.eil-infra.com" >> /etc/hosts
    echo "${EIL_STAGING} eilstaging  eilstaging.eil-infra.com" >> /etc/hosts
    echo "## EIL_END" >> /etc/hosts

    md5sum /etc/hosts > /etc/hosts.md5
}

# Start out by setting up our hosts file
make_hosts_file

# Obtain the latest release
WORKSPACE=`mktemp -d`
cd $WORKSPACE
wget -q "http://${EIL_STAGING}/release/eil_clientagent-release.tar.gz"
tar xzf eil_clientagent-release.tar.gz

# Before we start, we should ensure the old steward is shutdown, if it is
# installed and running
if [ -e "/etc/init.d/eil_steward.sh" ]; then
    /etc/init.d/eil_steward.sh stop
fi

# Give it a bit to stop what it's doing
sleep 5

cd eil_clientagent-release/
# First, uninstall the old one
./install_tool.sh -r --uninstall

# Begin the package install
./install_tool.sh -r --pkginstall

# Clean-up after ourselves
rm -f $THIS_SCRIPT

# vim:set ai et sts=4 sw=4 tw=80: