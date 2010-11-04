#!/bin/sh

# Install script for clientagent-base.sh suite

if [ "$(id -u)" != "0" ]; then
    echo "This install script must be run as root!"
    exit 1
fi

. lib/helper.sh
. lib/globals.sh

# Functions used by the install script
add_user_if_not_exist() {
    /bin/egrep -i "^$GID" /etc/group > /dev/null
    if [ $? -ne 0 ]; then
        # Group does not exist, add it
        if [ -n "$IS_SLES" ]; then
            /usr/sbin/groupadd $GID
        else
            /usr/sbin/groupadd -f $GID
        fi
        
    fi
    
    /bin/egrep -i "^$UID" /etc/passwd > /dev/null
    if [ $? -ne 0 ]; then
        # User does not exist, add them
        if [ -n "$IS_SLES" ]; then
            /usr/sbin/useradd -d /dev/null -c eil_client \
                -s /bin/false -g $GID $UID
        else
            /usr/sbin/useradd -d /dev/null -c eil_client \
                -s /dev/null -g $GID -M $UID
        fi
    fi
}

del_user_if_exist() {
    /bin/egrep -i "^$UID" /etc/passwd > /dev/null
    if [ $? -eq 0 ]; then
        /usr/sbin/userdel -f $UID
    fi
    
    /bin/egrep -i "^$GID" /etc/group > /dev/null
    if [ $? -eq 0 ]; then
        /usr/sbin/groupdel $GID
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

EXEC=clientagent-base.sh

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
                rm -f $LIB_DIR/*
                rmdir $LIB_DIR
                
                # purge the docs
                rm -f $DOC_DIR/*
                rmdir $DOC_DIR
                
                # purge the tools
                rm -f $TOOL_DIR/*
                rmdir $TOOL_DIR
                
                # purge the bin
                rm -f $BIN_DIR/*
                rmdir $BIN_DIR
                
                # purge the main directory
                rm -f $INSTALL_DIR/*
                rmdir $INSTALL_DIR
                
                # purge the users
                del_user_if_exist
                
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
cp -fr lib/globals.sh $LIB_DIR/.

# Install the tools

# Install the docs

# Install the binaries
cp -fr bin/$EXEC $BIN_DIR/.
chmod a+x $BIN_DIR/$EXEC

# Set up the rc files
# FIXME TODO

# Set up the users
add_user_if_not_exist
