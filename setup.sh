#!/bin/bash


#####################
# Project directory #
#####################
export BASE_DIR=$(pwd)

####################
# External Plugins #
####################
export POWERSUPPLYDIR=$BASE_DIR/../power_supply
export TCUSBDIR=$BASE_DIR/../cmsph2_tcusb

##########
# System #
##########
export PATH=$BASE_DIR/bin:$PATH
export LD_LIBRARY_PATH=$USBINSTLIB:$ANTENNALIB:$BASE_DIR/RootWeb/lib:$CACTUSLIB:$BASE_DIR/lib:$EUDAQLIB:/opt/rh/llvm-toolset-7.0/root/usr/lib64:$LD_LIBRARY_PATH:$TCUSBDIR:$POWERSUPPLYDIR

export CMAKE_MODULE_PATH=$CMAKE_MODULE_PATH:$BASE_DIR/cmake

#########
# Flags #
#########
export TCUSBFlag='-D__TCUSB__'
export PowerSupplyFlag='-D__POWERSUPPLY__'

echo "=== DONE ==="

