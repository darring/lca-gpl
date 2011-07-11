#!/usr/bin/env sh

# install_asset.sh
# --------------
# Install and set up the assetinfo as a postinst process

# Load our libraries
. /opt/intel/eil/clientagent/lib/helper.sh
. /opt/intel/eil/clientagent/lib/globals.sh

# THIS MUST ONLY BE RUN BY THE DISPATCHER INSTALL SCRIPT

clean_init() {
    if [ -e "/etc/init.d/assetinfo.sh" ]; then
        /etc/init.d/assetinfo.sh stop
        if [ -n "$IS_RHEL" ]; then
            chkconfig --del assetinfo.sh
        elif [ -n "$IS_DEB" ] || [ -n "$IS_ANGSTROM" ]; then
            update-rc.d -f assetinfo.sh remove
        elif [ -n "$IS_SLES" ]; then
            /usr/lib/lsb/remove_initd /etc/init.d/assetinfo.sh
        elif [ -n "$IS_ESX" ]; then
            # This is silly, just reboot the system :-P
            rm -f /etc/init.d/assetinfo.sh
            rm -f /etc/rc.local.d/assetinfo.sh
        fi
    fi
}

install_files() {
}

setup_init() {
}

# Clean up previous work (if any)
clean_init

# Perform our install
install_files
setup_init

# vim:set ai et sts=4 sw=4 tw=80:
