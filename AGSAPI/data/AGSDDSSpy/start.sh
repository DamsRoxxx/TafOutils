#!/bin/bash

INIT_PWD=`pwd`
cd $AGSAPI_PATH/AGSDDSSpy
# Set NDDSHOME to allow RTI to find the license and run the program
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../common/lib/ NDDSHOME=./rti_license/ ./bin/AGSDDSSpy $AGSAPI_DOMAIN_ID src/USER_QOS_PROFILES.xml
cd $INIT_PWD
