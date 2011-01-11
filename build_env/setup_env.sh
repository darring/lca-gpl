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
EOF
)


# vim:set ai et sts=4 sw=4 tw=80:
