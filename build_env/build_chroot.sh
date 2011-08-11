#!/usr/bin/env bash

# build_chroot.sh
# ---------------
# A tool to build a chroot in Ubuntu/Debian or SuSE-based systems for building
# the EIL Linux agent

MY_CWD=`pwd`

# We default to 'lucid', or Ubuntu 10.04. If you want to update that, feel free
# just know that you will need to make sure everything else works.
DEB_DISTRO="lucid"

SUSE_DISTRO="11.3"

# Must be run as root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root!"
    exit 1
fi

error_wrongDistro() {
cat <<EOF

 This script must be run in a Debian-derived distribution (such as Ubuntu) or
 in an openSUSE-derived distribution!

 If you wish to build the EIL Linux client agent in another distribution, please
 see the BUILD_ENV text file and the source for this script to find the proper
 dependencies necessary to set up your build environment!

EOF
}

error_missingPath() {
cat <<EOF

 Script requires a path agument for where the chroot will be located. Please
 run the script again with a path argument!

EOF
}

trace() {
    DATESTAMP=$(date +'%Y-%m-%d %H:%M:%S %Z')
    echo "${DATESTAMP} : ${*}"
}

run_setupenv() {
    local CHROOT_PATH=$1
    # run the setup_env from the chroot
    echo "#!/bin/sh" >> ${CHROOT_PATH}/root/run_once.sh
    echo "cd /root" >> ${CHROOT_PATH}/root/run_once.sh
    echo "./setup_env.sh" >> ${CHROOT_PATH}/root/run_once.sh

    chmod a+x ${CHROOT_PATH}/root/run_once.sh

    chroot ${CHROOT_PATH} /root/run_once.sh
}

deb_build() {
    local CHROOT_PATH=$1
    debootstrap ${DEB_DISTRO} ${CHROOT_PATH}

    # copy our items over into the chroot
    cp -frv gsoap-2.8 ${CHROOT_PATH}/root/.
    cp -fv deb_setup_env.sh ${CHROOT_PATH}/root/setup_env.sh
    chmod a+x ${CHROOT_PATH}/root/setup_env.sh

    # Mount our dev and proc
    mount --bind /proc ${CHROOT_PATH}/proc
    mount --bind /dev ${CHROOT_PATH}/dev

    # Make sure we have universe and multiverse in our sources list
    echo "deb http://archive.ubuntu.com/ubuntu ${DEB_DISTRO} universe" \
        >> ${CHROOT_PATH}/etc/apt/sources.list
    echo "deb http://archive.ubuntu.com/ubuntu ${DEB_DISTRO} multiverse" \
        >> ${CHROOT_PATH}/etc/apt/sources.list

    run_setupenv $CHROOT_PATH
}

suse_build() {
    local CHROOT_PATH=$1

    if [ ! -d "$CHROOT_PATH" ]; then
        mkdir -p ${CHROOT_PATH}
    fi

    zypper --root ${CHROOT_PATH} addrepo \
        http://download.opensuse.org/distribution/${SUSE_DISTRO}/repo/oss/ repo-oss
    zypper --root ${CHROOT_PATH} addrepo \
        http://download.opensuse.org/distribution/${SUSE_DISTRO}/repo/non-oss/ repo-non-oss
    zypper --root ${CHROOT_PATH} addrepo \
        http://download.opensuse.org/update/${SUSE_DISTRO}/ repo-update

    # Mount our dev and proc
    mkdir -p ${CHROOT_PATH}/proc
    mkdir -p ${CHROOT_PATH}/dev
    mount --bind /proc ${CHROOT_PATH}/proc
    mount --bind /dev ${CHROOT_PATH}/dev

    zypper --root ${CHROOT_PATH} --gpg-auto-import-keys -n \
        install --auto-agree-with-licenses zypper

    # copy our items over into the chroot
    #cp -frv gsoap-2.8 ${CHROOT_PATH}/root/.
    #cp -fv suse_setup_env.sh ${CHROOT_PATH}/root/setup_env.sh
    #chmod a+x ${CHROOT_PATH}/root/setup_env.sh

    echo "run_setupenv $CHROOT_PATH"
}

# Get our chroot path
if [ -n "$1" ]; then
    # determine which distro we're running
    if [ -f "/etc/debian_version" ]; then
        deb_build "${1}"
    elif [ -f "/etc/SuSE-release" ]; then
        suse_build "${1}"
    else
        error_wrongDistro
        exit 1
    fi
    cat <<EOF

 Your chroot environment at "${CHROOT_PATH}" is now set up and ready for active
 development!

EOF

else
    error_missingPath
fi

# vim:set ai et sts=4 sw=4 tw=80:
