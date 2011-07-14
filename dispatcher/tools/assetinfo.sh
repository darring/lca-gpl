#!/bin/bash

### BEGIN INIT INFO
# Provides:             assetinfo
# Required-Start:       $local_fs $syslog ipmidrv
# Required-Stop:        $local_fs $syslog ipmidrv
# Default-Start:        2 3 4 5
# Default-Stop:
# Short-Description:    asset collection script
# Description:          asset collection script
### END INIT INFO

# RHEL information
# chkconfig: 2345 80 20
# description: asset collection script

IPMITOOL=/usr/bin/ipmitool
DCMITOOL=/usr/local/bin/dcmitool
DMIDECODE=/usr/sbin/dmidecode

FUNCT_ARRAY=("turbo" "hyperthreading" "vt" "vt-d" "Xd" "UUID" "c6state" "c2c4state"
             "nmver" "dcmiver" "eist" "dimmslots" "dimmspop" "ramtotal" "dimm"
             "sr-iov" "niccount" "nicspeed" "fibercount" "fiberspeed" "sol"
             "remote" "hdcount" "raid" "oem")

printstart() {
 echo "<Attributes>"
}
printend() {
 echo "</Attributes>"
}

turbo() { #<Turbo>Enabled/Disabled</Turbo>
 echo "<Turbo>N/A</Turbo>" 
}

hyperthreading() { #<HyperThreading>Enabled/Disabled</HyperThreading>
 echo -n "<HyperThreading>"
 if grep ht /proc/cpuinfo &> /dev/null; then 
  echo -n "Enabled"
 else
  echo -n "Disabled"
 fi
 echo "</HyperThreading>"
}

vt() { #<Vt>Enabled/Disabled</Vt>
 echo "<Vt>N/A</Vt>"
}

vt-d() { #<Vt-d>Enabled/Disabled</Vt-d>
 echo "<Vt-d>N/A</Vt-d>"
}

Xd() { #<Xd>Enabled/Disabled</Xd>
 echo "<Xd>N/A</Xd>"
}

UUID() { #<UUID>Urbanna</UUID>                
 echo -n "<UUID>"
 uuid=`$DMIDECODE| grep UUID | awk '{print $2}'`
 echo -n "$uuid"
 echo "</UUID>"
}

c6state() { #<C6State>Enabled/Disabled</C6State>
 echo "<C6State>N/A</C6State>"
}

c2c4state() { #<C2C3>Enabled/Disabled</C2C3>
 echo "<C2C3>N/A</C2C3>"
}

nmver() { #<NMVersion>1.5</NMVersion>
 echo -n "<NMVersion>"
 bmc_v=`$IPMITOOL mc info | grep IPMI | awk '{print $4}' 2>/dev/null`
 BMC_VER="Disabled"
 if [ "$bmc_v" == "2.0" ]; then
  BMC_VER="1.5"
 fi
 if [ "$bmc_v" == "2" ]; then
  BMC_VER="1.5"
 fi
 if [ "$bmc_v" == "3.0" ]; then
  BMC_VER="2.0"
 fi
 echo  -n "$BMC_VER"
 echo "</NMVersion>"
}

dcmiver() { #<DCMIVersion>1.5</DCMIVersion>
 echo -n "<DCMIVersion>"
 v=`$DCMITOOL  raw 0x2c 0x01 0xdc 0x01 | awk '{print $2"."$3}'`
 echo -n "$v"
 echo "</DCMIVersion>"
}

eist() { #<EIST>Enabled/Disabled</EIST>
 echo "<EIST>N/A</EIST>"
}

dimmslots() { #<DimmSlots>4</DimmSlots>
 echo -n "<DimmSlots>"
 cnt=`$DMIDECODE | grep "Memory Device" | wc -l`
 echo -n "$cnt"
 echo "</DimmSlots>"
}

dimmspop() { #<DimmPopulated>4</DimmPopulated>
 echo -n "<DimmPopulated>"
 cnt=`$DMIDECODE | grep "Memory Device" -A 17 | grep "Size" | grep -v "No Module Installed" | wc -l`
 echo -n "$cnt"
 echo "</DimmPopulated>"
}

ramtotal() { #<RamTotal>12</RamTotal>
 echo -n "<RamTotal>"
 result=`$DMIDECODE | grep "Memory Array" -A 6 | grep Range | awk '{print $3$4}'`
 echo -n "$result"
 echo "</RamTotal>"
}

dimm() { #<Dimm><DimmSpeed>1066</DimmSpeed><DimmSize>2</DimmSize></Dimm>
 echo "<Dimm>"
 for dimm in `$DMIDECODE | grep "Memory Device" -A 17 | grep "Size" | grep -v "No Module" | awk '{print $2$3}'`; do
  echo -n "<DimmSize>"
  echo -n "$dimm"
  echo    "</DimmSize>"  
 done
 echo "</Dimm>"
}

sr-iov() { #<SR-IOV>Enabled/Disabled</SR-IOV>
 echo "<SR-IOV>N/A</SR-IOV>"
}

niccount() { #<NicCount>2</NicCount>
 echo -n "<NicCount>"
 cnt=`ifconfig -a| grep eth | wc -l`
 echo -n "$cnt"
 echo "</NicCount>"
}

nicspeed() { #<NicSpeed>1Gb</NicSpeed>
 for i in "`dmesg | grep eth | grep Mbps`"; do
  speed=`echo $i | awk '{print $7 " " $8}'` 
  echo "<NicSpeed>$speed</NicSpeed>"
 done
}

FC_DIR=/sys/class/fc_host

fibercount() { #<FiberCount>2</FiberCount>
 echo -n "<FiberCount>"
 if [ ! -d $FC_DIR ]; then
  echo -n "0"
 else
  PORT_CNT=`ls -1 $FC_DIR| wc -l`
  echo -n "$PORT_CNT"
 fi
 echo "</FiberCount>"
}

fiberspeed() { #<FiberSpeed>1Gb</FiberSpeed>
 if [ -d $FC_DIR ]; then 
  for i in `ls -1 $FC_DIR`; do
   echo -n "<FiberSpeed>"
   SPEEDS=`cat $FC_DIR/$i/supported_speeds`
   echo -n "$SPEEDS"
   echo "</FiberSpeed>"
  done
 else
  echo "<FiberSpeed>Disabled</FiberSpeed>"
 fi
}

sol() { #<SerialOverLan>Enabled/Disabled</SerialOverLan>
 echo -n "<SerialOverLan>"
 test=` $IPMITOOL sol info 1 | grep Enabled | awk '{print $3}'`
 if [ "$test" == "true" ]; then
  echo -n "Enabled"
 else
  echo -n "Disabled"
 fi
 echo "</SerialOverLan>"
}

remote() { #<RemoteCapability><IPaddress>10.19.253.1</IPaddress><Weblink>http://10.19.253.1</Weblink><iLO></iLO></RemoteCapability> 
 echo "<RemoteCapability>"
  echo -n "<IPaddress>"
  ip=`$IPMITOOL lan print | grep "IP Addr" | grep -v Source | awk '{print $4}'`
  echo -n "$ip"
  echo "</IPaddress>"
  echo "<Weblink>http://$ip</Weblink>"
  echo "<iLO></iLO>"
 echo "</RemoteCapability>"
}

hdcount() { #<HardDriveCount>3</HardDriveCount>
 echo -n "<HardDriveCount>"
 cnt=` fdisk -l | grep "^Disk" | cut -f 1 -d ',' | cut -f 3- -d '/' | wc -l`
 echo -n "$cnt"
 echo "</HardDriveCount>"
}

raid() { #<Raid>Enabled/Disabled</Raid>
 echo -n "<Raid>"
 if dmesg | grep raid| grep PCI &> /dev/null; then 
  echo -n "Enabled"
 else
  echo -n "Disabled"
 fi
 echo "</Raid>"
}

oem() { #<OEMInventory><Bios>1.5</Bios><BMC>2.11</BMC></OEMInventory>
 echo "<OEMInventory>"
 echo "<Bios>N/A</Bios>"
 echo -n "<BMC>"
 ver=` $IPMITOOL mc info | grep Firmware | grep -v Aux | awk '{print $4}'`
 echo -n "$ver"
 echo "</BMC>"
 
 echo "</OEMInventory>"
}

collectInfo() {
 if [ ! -d /opt/intel ]; then
  mkdir -p /opt/intel
 fi
 ASSET_FILE=/opt/intel/assetinfo
 printstart > $ASSET_FILE
 for funct in "${FUNCT_ARRAY[@]}"; do
  ${funct} >> $ASSET_FILE
 done
 printend >> $ASSET_FILE
}

if [ -f /lib/lsb/init-functions ]; then
 . /lib/lsb/init-functions 
fi

case "$1" in
start|restart)
    collectInfo
    exit 0
    ;;
esac
exit 0