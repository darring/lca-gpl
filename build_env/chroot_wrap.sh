#!/usr/bin/env bash

# chroot_wrap.sh
# --------------
# Very simple tool to wrap chrooting into a build environment

MY_CWD=`pwd`

# Must be run as root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root!"
    exit 1
fi

# Get our chroot path
if [ -n "$1" ]; then
    CHROOT_PATH=$1
fi

# vim:set ai et sts=4 sw=4 tw=80:
