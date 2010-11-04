#!/bin/sh

# Install script for clientagent-base.sh suite

. lib/helper.sh

# Functions used by the install script
add_user_if_not_exist() {
  /bin/egrep  -i "^$@" /etc/passwd > /dev/null
  if [ $? -eq 0 ]; then
    # User exists
  else
    # User does not exist
  fi
}

# We use /opt for our installation location to adhere to LSB Linux
# Filesystem Hierarchy Standards (this gives us maximum compatibility
# across the various distros we aim to support).
BASE_DIR=/opt

# Intel has a registered provider name with the LSB
LANANA=$BASE_DIR/intel

# We want to have our own sub-directory under that specific to the
# EIL namespace, additionally, we want our client agent to live there.
INSTALL_DIR=$LANANA/eil/clientagent

BIN_DIR=$INSTALL_DIR/bin
LIB_DIR=$INSTALL_DIR/lib
DOC_DIR=$INSTALL_DIR/doc
TOOL_DIR=$INSTALL_DIR/tools

# Our user and group will be eil.eil
USER=eil
GROUP=eil

if [ $# != 0 ] ; then
    while true ; do
        case "$1" in
            -h)
                echo "install.sh"
                echo "----------"
                echo "Run with no arguments to install software"
                echo "Run with '-p' to purge/remove old software"
                exit 0
                ;;
            -p)
                # FIXME TODO
                # purge the libs
                
                # purge the docs
                
                # purge the tools
                
                # purge the bin
                
                # purge the users
                
                # purge the rc files
                
                echo "clientagent-base.sh purged"
                exit 0
                ;;
            *)
                break
                ;;
        esac
    done
fi

# Make the entire directory tree, including bin, libs, docs, etc.
mkdir -p $INSTALL_DIR
mkdir -p $BIN_DIR
mkdir -p $LIB_DIR
mkdir -p $DOC_DIR
mkdir -p $TOOL_DIR

# Install the libs
cp -fr libs/globals.sh $LIB_DIR/.

# Install the tools

# Install the docs

# Install the binaries
cp -fr bin/clientagent-bin.sh $BIN_DIR/.
chmod a+x $BIN_DIR/clientagent-bin.sh

# Set up the rc files
# FIXME TODO

# Set up the users
