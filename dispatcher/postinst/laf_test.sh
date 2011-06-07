#!/usr/bin/env sh

# laf_test.sh
# -----------
# Test script to determine if the system should run the laf post install
# scripts

# THIS MUST ONLY BE RUN BY THE DISPATCHER INSTALL SCRIPT

# Load our libraries
. /opt/intel/eil/clientagent/lib/helper.sh
. /opt/intel/eil/clientagent/lib/globals.sh

INSTALL_DEPS=$(cat <<EOF
wget
bash
EOF
)

# FIXME - This is pretty ugly, any paths with ':" or "," in them will wreck it
# however, it should be safe for now
CLEAN_PATH=$(echo $PATH | sed "s/:/,/g" | sed -f ${LIB_DIR}/comma_split.sed)

_check_file_in_path() {
    RET_VAL=1
    for P in $CLEAN_PATH
    do
        if [ -e "${P}/${1}" ]; then
            RET_VAL=0
            break
        fi
    done
    return $RET_VAL
}

# FIXME - For now, we just return true

# TODO - The REQ_PROGS section of install_laf.sh needs to be folded into this
#   test script. (See dispatcher/docs/NMSA)
check_req_progs() {
    RET_VAL=1
    for APP_TO_CHECK in $INSTALL_DEPS
    do
        _check_file_in_path $APP_TO_CHECK
        _STATUS=$?
        if [ "${_STATUS}" -eq "0" ]; then
            RET_VAL=0
            break
        fi
    done
    return $RET_VAL
}

# TODO - This test script should output a filesystem toggle that indicates to
#   the steward whether to run the NMSA process

exit 0

# vim:set ai et sts=4 sw=4 tw=80:
