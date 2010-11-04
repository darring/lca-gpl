# Helper functions used by all client agent code

# Determine what we're running. This is a bit messy, but hey, we're
# running in bash, we can't *really* use anything more advanced.
unset IS_RHEL IS_DEB IS_SLES IS_ESX IS_XEN || true

if [ -f "/etc/debian_version" ]; then
    IS_DEB=yes
elif [ -f "/etc/redhat-release" ]; then
    IS_RHEL=yes
elif [ -f "/etc/novell-release" ]; then
    IS_SLES=yes
fi

# vim:set ai et sts=4 sw=4 tw=80:
