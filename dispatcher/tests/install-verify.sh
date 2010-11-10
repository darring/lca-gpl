#!/usr/bin/env bash

# install-verify.sh
# -----------------
# Verifies that the install script for the dispatcher works

. ../lib/globals.sh

# Set up our environment
oneTimeSetUp()
{
    # Obtain a tmp directory to install to
    # TODO
    TMP_DIR="/tmp/clientagent."
    TMP_DIR=${TMP_DIR}$(date +%j%H%M%S)
    mkdir -p ${TMP_DIR}

    # Install to tmp directory
    BOOTSTRAP_DIR=$TMP_DIR
    export BOOTSTRAP_DIR
    cd ../
    #bash install.sh

    cd tests/
}

# Tear down our environment
oneTimeTearDown()
{
    # Clean up tmp directory
    # TODO
    BOOTSTRAP_DIR=$TMP_DIR
    export BOOTSTRAP_DIR
    cd ../
    #bash install.sh -p

    cd tests/
}

#######################
# Our actual unit tests
#######################

# Test that the UID was actually added
testUserWasAdded()
{
    egrep -i "^$INSTALL_UID" /etc/passwd > /dev/null
    if [ $? -ne 0 ]; then
        fail "User ${INSTALL_UID} was not added during install!"
    else
        assertTrue ${SHUNIT_TRUE}
    fi
}

# Test that the GID was actually added
testGroupWasAdded()
{
    egrep -i "^$INSTALL_GID" /etc/group > /dev/null
    if [ $? -ne 0 ]; then
        fail "Group ${INSTALL_GID} was not added during install!"
    else
        assertTrue ${SHUNIT_TRUE}
    fi
}

. /usr/share/shunit2/shunit2
