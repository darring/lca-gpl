#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
#!/bin/bash 

######################
# relay.sh           #
######################

LOCK_FILE=/opt/intel/eil/relay/relay.lock
SID_DIR=/opt/intel/eil/laf/sids/
OUTPUT_DIR=/opt/intel/eil/laf/output
TMP_PROXY=$http_proxy
HOSTNAME=`/bin/hostname`

function clear_proxy {
 http_proxy=""
}

function restore_proxy {
 http_proxy=$TMP_PROXY
}

function update_sids {
 for sid in `ls $SID_DIR`; do
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=1&log="
  clear_proxy
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 done
}

function run_workload {
 sid=$1
 workload=$2
 echo "running workload $sid $workload"
 /opt/intel/eil/laf/bin/laf.sh $sid $workload
 return $?
}

function command_query {
 QUERY_URL="10.4.1.6/client_poll.php?mac=00:1B:21:44:F0:C4&hostname=$HOSTNAME"
 echo "using query url -> $QUERY_URL"
 clear_proxy
 wget -O /tmp/query.url $QUERY_URL &> /dev/null
 restore_proxy
 if ! grep nothing /tmp/query.url &> /dev/null;then 
#this should really check for more then nothing and workload info
#because its possible for this to be "register" which means 
#we need to registeR  
  sid=`cat /tmp/query.url | awk '{print $1}'`
  workload=`cat /tmp/query.url | awk '{print $2}'`
  run_workload $sid $workload
  ret=$?
  UPDATE_URL="10.4.1.6/client_push.php?mac=00:1B:21:44:F0:C4&sid=$sid&comp=$ret&log=relay.sh-`date "+%m-%d-%y-%H_%M"|sed -e 's/ /+/g' `-`cat $OUTPUT_DIR/$sid`"
  clear_proxy
  echo "using update_url -> $UPDATE_URL"
  wget -O /dev/null "$UPDATE_URL" &> /dev/null
  restore_proxy
 fi
}

if [ ! -e $LOCK_FILE ]; then
 touch $LOCK_FILE
 command_query
 rm $LOCK_FILE
fi
