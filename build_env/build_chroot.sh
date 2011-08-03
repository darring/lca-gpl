#!/usr/bin/env bash

# build_chroot.sh
# ---------------
# A tool to build a chroot in Ubuntu/Debian or SuSE-based systems for building
# the EIL Linux agent

MY_CWD=`pwd`

# We default to 'lucid', or Ubuntu 10.04. If you want to update that, feel free
# just know that you will need to make sure everything else works.
DISTRO="lucid"

# Must be run as root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root!"
    exit 1
fi

trace() {
    DATESTAMP=$(date +'%Y-%m-%d %H:%M:%S %Z')
    echo "${DATESTAMP} : ${*}"
}

deb_build() {
    CHROOT_PATH=$1
    debootstrap lucid ${CHROOT_PATH}

    # copy our items over into the chroot
    cp -frv gsoap-2.8 ${CHROOT_PATH}/root/.
    cp -fv setup_env.sh ${CHROOT_PATH}/root/.
    chmod a+x ${CHROOT_PATH}/root/setup_env.sh

    # Mount our dev and proc
    mount --bind /proc ${CHROOT_PATH}/proc
    mount --bind /dev ${CHROOT_PATH}/dev

    # Make sure we have universe and multiverse in our sources list
    echo "deb http://archive.ubuntu.com/ubuntu lucid universe" \
        >> ${CHROOT_PATH}/etc/apt/sources.list
    echo "deb http://archive.ubuntu.com/ubuntu lucid multiverse" \
        >> ${CHROOT_PATH}/etc/apt/sources.list

    # run the setup_env from the chroot
    echo "#!/bin/sh" >> ${CHROOT_PATH}/root/run_once.sh
    echo "cd /root" >> ${CHROOT_PATH}/root/run_once.sh
    echo "./setup_env.sh" >> ${CHROOT_PATH}/root/run_once.sh

    chmod a+x ${CHROOT_PATH}/root/run_once.sh

    chroot ${CHROOT_PATH} /root/run_once.sh
}

# Get our chroot path
if [ -n "$1" ]; then
    # determine which distro we're running
    if [ -f "/etc/debian_version" ]; then
        deb_build "${1}"
    else if [ ! -f "/etc/SuSE-release" ];
    else
        cat <<EOF

 This script must be run in a Debian-derived distribution (such as Ubuntu) or
 in an openSUSE-derived distribution!

 If you wish to build the EIL Linux client agent in another distribution, please
 see the BUILD_ENV text file and the source for this script to find the proper
 dependencies necessary to set up your build environment!

EOF

        exit 1
    fi
    cat <<EOF

 Your chroot environment at "${CHROOT_PATH}" is now set up and ready for active
 development!

EOF

else
    cat <<EOF

 Script requires a path agument for where the chroot will be located. Please
 run the script again with a path argument!

EOF

fi

# vim:set ai et sts=4 sw=4 tw=80:
