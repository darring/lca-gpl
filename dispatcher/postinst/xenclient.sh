#!/usr/bin/env bash

# XenClient Specific post installation tool
# -----------------------------------------
# This post-install script fixes various platform specific problems that occur
# during the install for XenClient systems

# The only thing we have to do, is fix crontab (since XenClient doesn't have
# proper cron directory delineations
crontab_line="0 * * * *   /opt/intel/eil/clientagent/tools/update-checker.sh"

echo "$(crontab_line)" >> /etc/cron/crontabs/root

# vim:set ai et sts=4 sw=4 tw=80:
