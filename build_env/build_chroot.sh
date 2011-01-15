#!/usr/bin/env bash

# build_chroot.sh
# ---------------
# A tool to build a chroot in Ubuntu/Debian for building the EIL Linux agent

MY_CWD=`pwd`

# Must be run as root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root!"
    exit 1
fi

# Check we're running debian/ubuntu
if [ ! -f "/etc/debian_version" ]; then
    cat <<EOF

 This script must be run in a Debian-derived distribution (such as Ubuntu)!

 If you wish to build the EIL Linux client agent in another distribution, please
 see the BUILD_ENV text file and the source for this script to find the proper
 dependencies necessary to set up your build environment!

EOF

exit 1
fi


# vim:set ai et sts=4 sw=4 tw=80:
