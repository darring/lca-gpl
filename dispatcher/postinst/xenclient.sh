#!/usr/bin/env bash

# XenClient Specific post installation tool
# -----------------------------------------
# This post-install script fixes various platform specific problems that occur
# during the install for XenClient systems

# The only thing we have to do, is fix crontab (since XenClient doesn't have
# proper cron directory delineations
crontab_line="0 * * * *   /opt/intel/eil/clientagent/tools/update-checker.sh"

crontab="/etc/cron/crontabs/root"

# This function cleans the previous hosts file
clean_crontab_file() {
    local TMP_FILE=`mktemp /tmp/eil-XXXXXX`
    sed '/## EIL_BEGIN/,/## EIL_END/d' ${crontab} > ${TMP_FILE}
    cp -f ${TMP_FILE} ${crontab}
    rm -f ${TMP_FILE}
}

clean_crontab_file

echo "## EIL_BEGIN" >> ${crontab}
echo "${crontab_line}" >> ${crontab}
echo "## EIL_END" >> ${crontab}

# vim:set ai et sts=4 sw=4 tw=80:
