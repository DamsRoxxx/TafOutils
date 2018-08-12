#!/bin/bash

source ./config.sh

./stop.sh
$AGSAPI_PATH/AGSDBFeeder/start.sh > /dev/null 2>&1 &
sleep 15
$AGSAPI_PATH/AGSAPIProvider/start.sh > /dev/null 2>&1 &
$AGSAPI_PATH/AGSWebClient/start.sh > /dev/null 2>&1 &
