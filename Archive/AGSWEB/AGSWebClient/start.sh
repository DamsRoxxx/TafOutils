#!/bin/bash

INIT_PWD=`pwd`
cd $AGSAPI_PATH/AGSWebClient/src
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../common/lib/ PYTHONPATH=$PYTHONPATH:../../common/lib/python/ python ./AGSWebClient.py
cd $INIT_PWD
