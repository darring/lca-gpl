#!/usr/bin/env sh

# install_laf.sh
# --------------
# Install and set up the LAF scripts as a postinst process

# THIS MUST ONLY BE RUN BY THE DISPATCHER INSTALL SCRIPT

INSTALL_CWD=$1

INSTALL_DIR=/opt/intel/eil/laf

CREATE_DIR=$(cat <<EOF
bin
log
output
sids
EOF
)

INSTALL_FILES=$(cat <<EOF
laf.sh
laf-lib.sh
relay.sh
EOF
)

clean_up() {
    for DIR in $CREATE_DIR
    do
        rm -f $INSTALL_DIR/$DIR/*
        rmdir --ignore-fail-on-non-empty $INSTALL_DIR/$DIR
    done

    rmdir --ignore-fail-on-non-empty $INSTALL_DIR
}

create_dir() {
    if [ ! -d $INSTALL_DIR ]; then
        mkdir -p $INSTALL_DIR
    fi

    for DIR in $CREATE_DIR
    do
        mkdir -p $INSTALL_DIR/$DIR
    done
}

install_files() {
    for FILE_TO_INSTALL in $INSTALL_FILES
    do
        cp -f ${INSTALL_CWD}/tools/${FILE_TO_INSTALL} \
                ${INSTALL_DIR}/bin/${FILE_TO_INSTALL}

        # TODO - Any permisions or ownership necessary here?
        chown root.root ${INSTALL_DIR}/bin/${FILE_TO_INSTALL}
    done
}

# Clean up any previous installation, setup for new installation and install
clean_up
create_dir

install_files

# vim:set ai et sts=4 sw=4 tw=80:
