#!/bin/sh

# Client agent base (Bash prototype)
# ----------------------------------
# This base takes commands that have already been parsed by another
# application and executes them based up certain criteria. It is
# intended to be fairly lean and require a minimal amount of external
# dependencies (e.g., it should run on a wide variety of platforms with
# minimal additional dependency installation)
#
# Please see the associated INSTALL and README files for more
# information

unset DEBUG || true


if [ "$TMP_DIR" = "" ]; then
    TMP_DIR="/tmp/clientagent."
    TMP_DIR=${TMP_DIR}$(date +%j%H%M%S)
fi
