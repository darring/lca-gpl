#!/usr/bin/env bash

# helper-verify.sh
# ----------------
# Verifies that the output given from clientagent-helper.sh is what is
# expected from globals.sh

# Set up our environment
oneTimeSetUp()
{
    # Obtain a tmp directory to install to
    TMP_DIR="/tmp/clientagent."
    TMP_DIR=${TMP_DIR}$(date +%j%H%M%S)
    mkdir -p ${TMP_DIR}

    # Install to tmp directory
    BOOTSTRAP_DIR=$TMP_DIR
    export BOOTSTRAP_DIR
    cd ../
    bash install.sh

    cd tests/

    . ../lib/globals.sh
}

# Tear down our environment
oneTimeTearDown()
{
    # Clean up tmp directory
    BOOTSTRAP_DIR=$TMP_DIR
    export BOOTSTRAP_DIR
    cd ../
    bash install.sh -p

    cd tests/
}

#######################
# Our actual unit tests
#######################

# Test each of the directory outputs
testBase()
{
    local base_test=`${TOOL_DIR}/clientagent-helper.sh --base`

    assertEquals "Base directory error!" \
        "${BASE_DIR}" "${base_test}"
}

. /usr/share/shunit2/shunit2
