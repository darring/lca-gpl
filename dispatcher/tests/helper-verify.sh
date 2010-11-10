#!/usr/bin/env bash

# helper-verify.sh
# ----------------
# Verifies that the output given from clientagent-helper.sh is what is
# expected from globals.sh

# Set up our environment
oneTimeSetUp()
{
    # Obtain a tmp directory to install to
    # TODO
    TMP_DIR="/tmp/clientagent."
    TMP_DIR=${TMP_DIR}$(date +%j%H%M%S)
    mkdir -p ${TMP_DIR}

    BOOTSTRAP_DIR=$TMP_DIR
    export BOOTSTRAP_DIR
    ../install.sh

    # Install to tmp directory
    # TODO
}

# Tear down our environment
oneTimeTearDown()
{
    # Clean up tmp directory
    # TODO
    echo "Test"
}

# Our actual unit tests
# TODO

#. /usr/share/shunit2/shunit2

oneTimeSetUp

echo $TMP_DIR
