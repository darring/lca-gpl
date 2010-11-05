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
