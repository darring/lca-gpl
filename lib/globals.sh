# Global variables to be used by the client agent

###################
# UID/GID settings
###################

UID="eil"
GID="eil"

####################################
# Basic logging and error reporting
####################################

# Note that these will be inside the home directory as defined
# elsewhere
STANDARD_LOG_FILE="${HOME}/client-agent-base.log"
CCMS_LOG_FILE="${HOME}/ccms-agent.log"
ERROR_LOG_FILE="${HOME}/client-agent-error.log"

###############################
# Communication layer settings
###############################

# Note that, again, these will be inside the home directory as
# defined elsewhere
COMMAND_DIR="${HOME}/commands"

# vim:set ai et sts=4 sw=4 tw=80:
