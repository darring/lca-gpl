#!/usr/bin/env sh

# install_laf.sh
# --------------
# Install and set up the LAF scripts as a postinst process

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
EOF
)

INSTALL_CWD=$1

# TODO - Move these into the laf_test script
#REQ_PROGS=("wget")

#has_cmd() {
# ret=0;
# cmd=$1
# shift
# tmp_f=/tmp/`date +%m%d%y-%M%S`
# whereis $cmd > $tmp_f
# if [ ! $? -eq 0 ]
# then
#  logerr $client 6 "+1"
#  return 1
# fi
# str=`cat $tmp_f | awk '{print $2}'`
# if [ ! -n "$str" ]
# then
#  ret=1
# fi
# rm $tmp_f
# return $ret
#}

#check_req_progs() {
# ret=0
# for prog in "${REQ_PROGS[@]}"; do
#  has_cmd $prog
#  if [ $? -eq 1 ]; then
#   echo "Missing required program $prog.  Please install and then try again"
#   ret=1
#   break
#  fi
# done
# return $ret
#}

clean_up() {
    for DIR in $CREATE_DIR
    do
        rm -f $INSTALL_DIR/$DIR
        rmdir --ignore-fail-on-non-empty $INSTALL_DIR/$DIR
    done

    rmdir --ignore-fail-on-non-empty $INSTALL_DIR/$DIR
}

create_dir() {
    if [ ! -d $INSTALL_DIR ]; then
# We can safely assume these will be setup by the Linux client agent.
# TODO - Remove once we're certain we can
#        if [ ! -d /opt/intel/eil ]; then
#            if [ ! -d /opt/intel ]; then
#                mkdir /opt/intel
#            fi
#            mkdir /opt/intel/eil
#        fi
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
        cp -f ${INSTALL_CWD}/${FILE_TO_INSTALL} \
                ${INSTALL_DIR}/bin/${FILE_TO_INSTALL}

        # TODO - Any permisions or ownership necessary here?
    done
}

# TODO - Remove the following, safe to assume it will be run as root by
# instaler
#LUID=$(id -u)
#if [[ $LUID -ne 0 ]]; then
# echo "Please run install script as root"
# exit 1
#fi

#check_req_progs
#if [ ! $? -eq 0 ]; then
# echo "Please install missing programs and then run installer again"
# exit 1
#fi

# Clean up any previous installation then setup for new installation
clean_up
create_dir

install_files
#cp src/*.sh $INSTALL_DIR/bin

# vim:set ai et sts=4 sw=4 tw=80:
