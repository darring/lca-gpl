#!/bin/sh

# The client agent bootstrap script
#----------------------------------
# This script is intended to bootstrap the EIL Linux Client Agent
#
# This script must be completely self-contained (unfortunately)

# EIL IP configs
EIL_AUTO="172.16.3.10"
EIL_STAGING="10.4.0.26"

THIS_SCRIPT=$0

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
    cp -f /etc/hosts /etc/hosts.backup.%{DATE_STAMP}
    md5sum /etc/hosts.backup.%{DATE_STAMP} > /etc/hosts.backup.md5.%{DATE_STAMP}

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

# Begin the package install
cd eil_clientagent-release/
./install_tool.sh -r --pkginstall

# Clean-up after ourselves
rm -f $THIS_SCRIPT
