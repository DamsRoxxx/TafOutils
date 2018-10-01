#!/bin/bash

source /appli/AGSAPI/comp/param/config.sh

./stop.sh

$AGSAPI_PATH/AGSDDSSpy/start.sh > /dev/null 2>&1 &
$AGSAPI_PATH/AGSAPIProvider/start.sh > /dev/null 2>&1 &
$AGSAPI_PATH/AGSWebClient/start.sh > /dev/null 2>&1 &
