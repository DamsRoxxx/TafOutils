#!/bin/bash

INIT_PWD=`pwd`
cd $AGSAPI_PATH/AGSAPIProvider/src
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../common/lib/ PYTHONPATH=$PYTHONPATH:../../common/lib/python/ python ./AGSAPIProvider.py ../../DATABASE.cfg
cd $INIT_PWD
