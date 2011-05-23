#!/usr/bin/env sh

# laf_test.sh
# -----------
# Test script to determine if the system should run the laf post install
# scripts

# THIS MUST ONLY BE RUN BY THE DISPATCHER INSTALL SCRIPT

# Load our libraries
. /opt/intel/eil/clientagent/lib/helper.sh
. /opt/intel/eil/clientagent/lib/globals.sh

# FIXME - For now, we just return true

# TODO - The REQ_PROGS section of install_laf.sh needs to be folded into this
#   test script. (See dispatcher/docs/NMSA)

# TODO - This test script should output a filesystem toggle that indicates to
#   the steward whether to run the NMSA process

exit 0

# vim:set ai et sts=4 sw=4 tw=80:
