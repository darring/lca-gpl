#!/usr/bin/env sh

# laf_test.sh
# -----------
# Test script to determine if the system should run the laf post install
# scripts

# THIS MUST ONLY BE RUN BY THE DISPATCHER INSTALL SCRIPT

# Load our libraries
. /opt/intel/eil/clientagent/lib/helper.sh
. /opt/intel/eil/clientagent/lib/globals.sh

unset WHEREIS || true

INSTALL_DEPS=$(cat <<EOF
wget
bash
EOF
)

# Unfortunately, we can't take as a given that whereis will be available due
# to the number of obscure platforms we support. Thus, we need to check them
# all.
POSSIBLE_WHEREIS_LOCATIONS=$(cat <<EOF
/usr/bin/whereis
/bin/whereis
EOF
)

# FIXME - For now, we just return true

# TODO - The REQ_PROGS section of install_laf.sh needs to be folded into this
#   test script. (See dispatcher/docs/NMSA)
check_req_progs() {
    RET_VAL=0
    for APP_TO_CHECK in $INSTALL_DEPS
    do
        
    done
}

# TODO - This test script should output a filesystem toggle that indicates to
#   the steward whether to run the NMSA process

exit 0

# vim:set ai et sts=4 sw=4 tw=80:
