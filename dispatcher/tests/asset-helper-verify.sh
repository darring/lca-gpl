#!/usr/bin/env bash

# asset-helper-verify.sh
# ----------------------
# Verifies the asset helper section of the code is in working condition

# Set up our environment
oneTimeSetUp()
{
    # Obtain a tmp directory
    TMP_DIR="/tmp/clientagent."
    TMP_DIR=${TMP_DIR}$(date +%j%H%M%S)
    mkdir -p ${TMP_DIR}

    # Set up our various temp file variables

    # Set up the asset source xml
    TMP_ASSET_SOURCE="${TMP_DIR}/asset_source.xml"
    cat > $TMP_ASSET_SOURCE << EOF
<Attributes>
<Turbo>N/A</Turbo>
<HyperThreading>Enabled</HyperThreading>
<Vt>N/A</Vt>
<Vt-d>N/A</Vt-d>
<Xd>N/A</Xd>
<UUID></UUID>
<C6State>N/A</C6State>
<C2C3>N/A</C2C3>
<NMVersion>Disabled</NMVersion>
<DCMIVersion></DCMIVersion>
<EIST>N/A</EIST>
<DimmSlots>0</DimmSlots>
<DimmPopulated>0</DimmPopulated>
<RamTotal></RamTotal>
<Dimm>
</Dimm>
<SR-IOV>N/A</SR-IOV>
<NicCount>1</NicCount>
<NicSpeed>is Up</NicSpeed>
<FiberCount>0</FiberCount>
<FiberSpeed>Disabled</FiberSpeed>
<SerialOverLan>Disabled</SerialOverLan>
<RemoteCapability>
<IPaddress></IPaddress>
<Weblink>http://</Weblink>
<iLO></iLO>
</RemoteCapability>
<HardDriveCount>0</HardDriveCount>
<Raid>Disabled</Raid>
<OEMInventory>
<Bios>N/A</Bios>
<BMC><BMC>
</OEMInventory>
</Attributes>
EOF

    TMP_ASSET_TEST="${TMP_DIR}/asset_test.xml"

    TMP_LOG="${TMP_DIR}/test.log"

    ASSET_FILE="/opt/intel/assetinfo"

    TMP_CURRENT_ASSET_STORAGE="${TMP_DIR}/asset_store"
    unset WAS_ORIG_ASSET || true
    if [ -e "${ASSET_FILE}" ]; then
        WAS_ORIG_ASSET=yes
        cp -f ${ASSET_FILE} ${TMP_CURRENT_ASSET_STORAGE}
    fi
}

# Tear down our environment
oneTimeTearDown()
{
    if [ -n "$WAS_ORIG_ASSET" ]; then
        cp -f ${TMP_CURRENT_ASSET_STORAGE} ${ASSET_FILE}
    fi
    rm -fr ${TMP_DIR}
}

#######################
# Our actual unit tests
#######################

testVerifyErrorOnNoAssetFile()
{
}


. /usr/share/shunit2/shunit2

# vim:set ai et sts=4 sw=4 tw=80:

