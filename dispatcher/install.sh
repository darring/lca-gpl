#!/usr/bin/env bash

# Install script for clientagent-base.sh suite

if [ "$(id -u)" != "0" ]; then
    echo "This install script must be run as root!"
    exit 1
fi

type hg &> /dev/null || { 
    type wget &> /dev/null || {
        type curl &> /dev/null || {
            cat <<EOF
One of the following programs are required by the clientagent dispatcher
in order for its auto-update/auto-patch features to work:
    * Mercurial (http://mercurial.selenic.com/)
    * wget (http://www.gnu.org/software/wget/)
    * curl (http://curl.haxx.se/)

Each should be available in any modern Linux distribution, and it is up
to you to determine which to use.

The preferred program is "Mercurial" as it allows for *both* auto-
updating and auto-patching, however, it has the most dependencies and
may not be easy to install on some of the more thin Linux installs.

Both wget and curl can do auto-update, but cannot do auto-patching.
EOF
            exit 1
        }
    }
}


. lib/helper.sh
. lib/globals.sh

# Parse the install dependency file
. ./install-deps.sh

# Functions used by the install script
add_user_if_not_exist() {
    local LGID=$2
    local LUID=$1
    if [ -z "$1" ]; then
        # If called with no parameters, we use the
        # defaults
        LUID=$INSTALL_UID
        LGID=$INSTALL_GID
    fi

    egrep -i "^$LGID" /etc/group > /dev/null
    if [ $? -ne 0 ]; then
        # Group does not exist, add it
        if [ -n "$IS_SLES" ]; then
            /usr/sbin/groupadd $LGID
        else
            /usr/sbin/groupadd -f $LGID
        fi

    fi

    egrep -i "^$LUID" /etc/passwd > /dev/null
    if [ $? -ne 0 ]; then
        # User does not exist, add them
        if [ -n "$IS_SLES" ]; then
            /usr/sbin/useradd -d $HOME_DIR -c eil_client \
                -s /bin/false -g $LGID $LUID
        else
            /usr/sbin/useradd -d /dev/null -c eil_client \
                -s /dev/null -g $LGID -M $LUID
        fi
    fi
}

del_user_if_exist() {
    egrep -i "^$INSTALL_UID" /etc/passwd > /dev/null
    if [ $? -eq 0 ]; then
        /usr/sbin/userdel -f $INSTALL_UID
    fi

    egrep -i "^$INSTALL_GID" /etc/group > /dev/null
    if [ $? -eq 0 ]; then
        /usr/sbin/groupdel $INSTALL_GID
    fi
}

uninstall_everything() {
    # uninstall the libs
    rm -f $LIB_DIR/*

    # uninstall the docs
    rm -f $DOC_DIR/*

    # uninstall the tools
    for TOOL_LINK in $LINKED_TOOLS
    do
        LARR=( `echo "$TOOL_LINK" | tr ':' '\n' ` )
        unlink ${LARR[1]}/${LARR[0]}
    done
    rm -f $TOOL_DIR/*

    # uninstall the scripts
    rm -f $SCRIPTS_DIR/*

    # uninstall the bin
    rm -f $BIN_DIR/*

    # uninstall the rc files
    # TODO
}

# We use /opt for our installation location to adhere to LSB Linux
# Filesystem Hierarchy Standards (this gives us maximum compatibility
# across the various distros we aim to support).
BASE_DIR=/opt

# Intel has a registered provider name with the LSB
LANANA=$BASE_DIR/intel

# We want to have our own sub-directory under that specific to the
# EIL namespace, additionally, we want our client agent to live there.
if [ "$BOOTSTRAP_DIR" = "" ]; then
    INSTALL_DIR=$LANANA/eil/clientagent
else
    INSTALL_DIR=$BOOTSTRAP_DIR
fi

BIN_DIR=$INSTALL_DIR/bin
LIB_DIR=$INSTALL_DIR/lib
DOC_DIR=$INSTALL_DIR/doc
TOOL_DIR=$INSTALL_DIR/tools
HOME_DIR=$INSTALL_DIR/home
SCRIPTS_DIR=$INSTALL_DIR/scripts

if [ $# != 0 ] ; then
    while true ; do
        case "$1" in
            -h)
                echo "install.sh"
                echo "----------"
                echo "Run with no arguments to install software."
                echo "Run with '-u' to uninstall old software without"
                echo "      purging log files or directory structure."
                echo "Run with '-p' to purge/remove old software."
                exit 0
                ;;
            -u)
                uninstall_everything
                echo "clientagent dispatcher uninstalled"
                exit 0
                ;;
            -p)
                uninstall_everything
                # purge the libs
                rmdir $LIB_DIR

                # purge the docs
                rmdir $DOC_DIR

                # purge the tools
                rmdir $TOOL_DIR

                # purge the scripts directory
                rmdir $SCRIPTS_DIR

                # purge the bin
                rmdir $BIN_DIR

                # purge the main directory
                rm -fr $INSTALL_DIR/*
                rmdir $INSTALL_DIR

                # purge the users
                del_user_if_exist

                # purge the rc files
                # TODO

                echo "clientagent dispatcher purged"
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
mkdir -p $HOME_DIR
mkdir -p $SCRIPTS_DIR

# Set up the users
add_user_if_not_exist

# Set ownership of the proper directories
chown ${INSTALL_UID}.${INSTALL_GID} ${HOME_DIR}
chmod 1777 ${HOME_DIR}

# Install the libs
for LIB_FILE in $ALL_LIBS
do
    cp -fr lib/${LIB_FILE} $LIB_DIR/.
done

# Install the tools
for TOOL_FILE in $ALL_TOOLS
do
    cp -fr tools/${TOOL_FILE} $TOOL_DIR/.
    chmod a+x ${TOOL_DIR}/${TOOL_FILE}
done

# Set up the linked tools
for TOOL_LINE in $LINKED_TOOLS
do
    LARR=( `echo "$TOOL_LINE" | tr ':' '\n' ` )

    cp ${LARR[2]} ${TOOL_DIR}/${LARR[0]} ${LARR[1]}/${LARR[0]}
done

# Install the docs
for DOC_FILE in $ALL_DOCS
do
    cp -fr docs/${DOC_FILE} $DOC_DIR/.
done

# Install the binaries
for EXEC_FILE in $ALL_EXECS
do
    cp -fr bin/$EXEC_FILE $BIN_DIR/.
    # Set up the binaries to SETUID as the user
    chown ${INSTALL_UID}.${INSTALL_GID} ${BIN_DIR}/${EXEC_FILE}
    chmod 754 ${BIN_DIR}/${EXEC_FILE}
    # SETUID/SETGID the binaries
    chmod u+s ${BIN_DIR}/${EXEC_FILE}
    chmod g+s ${BIN_DIR}/${EXEC_FILE}
done

# Install the scripts
# - Start with the source scripts
for SCRIPT_LINE in $SOURCE_SCRIPTS
do
    LARR=( `echo "$SCRIPT_LINE" | tr ':' '\n' ` )

    cp -fr scripts/${LARR[1]} ${SCRIPTS_DIR}/.
    if [ "${LARR[0]}" = "*.*" ]; then
        # Make it owned by the same owner as client agent dispatcher
        chown ${INSTALL_UID}.${INSTALL_GID} ${SCRIPTS_DIR}/${LARR[1]}
    else
        # Make it owned by the user specified
        chown ${LARR[0]} ${SCRIPTS_DIR}/${LARR[1]}
    fi

    # SETUID/SETGID
    chmod u+s ${SCRIPTS_DIR}/${LARR[1]}
    chmod g+s ${SCRIPTS_DIR}/${LARR[1]}
done

# - Now do the linked scripts

# Set up the rc files
# FIXME TODO

echo "clientagent dispatcher installed successfully"

# vim:set ai et sts=4 sw=4 tw=80:
