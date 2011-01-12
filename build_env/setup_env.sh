#!/usr/bin/env bash

# setup_env.sh
# ------------
# A tool to setup the build environment (Ubuntu/Debian specific)

# Make sure that (if in Ubuntu) the 'Universe' and 'Multiverse' are enabled in
# your sources list!

ALL_DEBS=$(cat <<EOF
dpkg-dev
build-essential
checkinstall
flex
automake
autoconf
autotools-dev
byacc
bison
libssl-dev
EOF
)

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

# Show interactive text explaining what we're about to do
cat <<EOF

 This script will set up a stock Debian or Ubuntu install for development and
 building of the EIL Linux client agent.

 If you are not using Debian or Ubuntu, then take a look at this script (and the
 BUILD_ENV text file) for more information about the EIL Linux client agent's
 requirements. If you are building or developing on a distribution other than
 Debian or Ubuntu, it is left up to you to figure out what is needed for a proper
 development environment.

 This script will have a number of interactive sections, please read everything
 carefully and answer the questions with caution.

EOF

read -p "Press [Enter] to continue : "

# Install the dependencies

cat <<EOF

 Updating aptitude....

EOF
aptitude update

cat <<EOF

 Installing dependencies...

 Select "Yes" if prompted...

EOF

aptitude install ${ALL_DEBS}

# Set up gsoap sources in a tmp directory

cat <<EOF

 Setting up gSOAP sources in a tmp build directory...

EOF



# configure and checkinstall

#configure
#make
#checkinstall

# vim:set ai et sts=4 sw=4 tw=80:
