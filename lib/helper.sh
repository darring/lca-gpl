# Helper functions used by all client agent code

# Determine what we're running. This is a bit messy, but hey, we're
# running in bash, we can't *really* use anything more advanced.
unset IS_RHEL IS_DEB IS_SLES IS_ESX IS_XEN || true
unset PLATFORM_NAME || true

# Given that we are running a Debian-derived distribution, find the
# specific Debian variant we are running.
find_specific_debian() {
    # For now, we just assume everything is compatible with Ubuntu,
    # this *probably* isn't the best assumption long-term, but until
    # we have customers screaming for Debian-specific installs, and
    # we find discrepencies, we'll just make due
    PLATFORM_NAME="ubuntu"
}

# Given that we are running a RedHat-derived distribution, find the
# specific RedHat variant we are running.
find_specific_redhat() {
    # Check for RHEL
    egrep -i "red hat enterprise" /etc/redhat-release > /dev/null
    if [ $? -ne 0 ]; then
        # Okay, let's see if we're CentOS
        egrep -i "centos" /etc/redhat-release > /dev/null
        if [ $? -ne 0 ]; then
            # Hmm, we don't know what to do here... Perhaps we should
            # exit with failure
            echo "ERROR! Unsupported Red Hat derivative!"
            echo "Check /etc/redhat-release for more information!"
            exit 1
        else
            # We're CentOS
            PLATFORM_NAME="centos"
        fi
    else
        # We're RHEL
        PLATFORM_NAME="rhel"
    fi
}

# Given that we are running a SuSE-derived distribution, find the
# specific SuSE variant we are running.
find_specific_suse() {

}

if [ -f "/etc/debian_version" ]; then
    find_specific_debian
    IS_DEB=yes
elif [ -f "/etc/redhat-release" ]; then
    find_specific_redhat
    IS_RHEL=yes
elif [ -f "/etc/novell-release" ]; then
    find_specific_suse
    IS_SLES=yes
fi

# vim:set ai et sts=4 sw=4 tw=80:
