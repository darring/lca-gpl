# Install file dependencies

# The executable files to install
ALL_EXECS=$(cat <<EOF
clientagent-dispatcher.sh
EOF
)

# The library files to install
ALL_LIBS=$(cat <<EOF
dispatcher.sh
globals.sh
helper.sh
EOF
)

# The tools to install
ALL_TOOLS=$(cat <<EOF

EOF
)

# The docs to install
ALL_DOCS=$(cat <<EOF

EOF
)
