#!/bin/bash

INIT_PWD=`pwd`
cd $AGSAPI_PATH/AGSDBFeeder
# Set NDDSHOME to allow RTI to find the license and run the program
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../common/lib/ NDDSHOME=./rti_license/ ./bin/AGSDBFeeder 7 src/USER_QOS_PROFILES.xml
cd $INIT_PWD
