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
EOF
)

# Check we're running debian/ubuntu

# Install the dependencies

# Set up gsoap sources in a tmp directory

# configure and checkinstall

configure
checkinstall

# vim:set ai et sts=4 sw=4 tw=80:
