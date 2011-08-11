#!/usr/bin/env bash

# suse_setup_env.sh
# ------------------
# A tool to setup the build environment (SUSE/openSUSE specific)

ALL_RPMS=$(cat <<EOF
flex
automake
autoconf
bison
mercurial
m4
gcc
gcc-c++
less
make
nano
perl
EOF
)

MY_CWD=`pwd`

# Must be run as root
if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root!"
    exit 1
fi

# Check we're running SuSE
if [ ! -f "/etc/SuSE-release" ]; then
    cat <<EOF

 This script must be run in a openSuSE-derived distribution (such as SLES)!

 If you wish to build the EIL Linux client agent in another distribution, please
 see the BUILD_ENV text file and the source for this script to find the proper
 dependencies necessary to set up your build environment!

EOF

exit 1
fi

# Show interactive text explaining what we're about to do
cat <<EOF

 This script will set up a stock openSuSE install for development and building
 of the EIL Linux client agent.

 If you are not using an openSuSE-derived distro, then take a look at this
 script (and the  BUILD_ENV text file) for more information about the EIL Linux
 client agent's  requirements.

 This script will have a number of interactive sections, please read everything
 carefully and answer the questions with caution.

EOF

read -p "Press [Enter] to continue : "

# Install the dependencies

zypper refresh

cat <<EOF

 Installing dependencies...

 Select "Yes" if prompted...

EOF

zypper install ${ALL_RPMS}

cat <<EOF

 Performing configure and package build for gsoap...

 Answer any questions asked...

EOF

read -p "Press [Enter] to continue : "

chmod a+x configure

./configure

# vim:set ai et sts=4 sw=4 tw=80:
