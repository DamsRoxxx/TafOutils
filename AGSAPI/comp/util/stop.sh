#!/bin/bash

source /appli/AGSAPI/comp/param/config.sh

for i in `ls $AGSAPI_PIDS_DIR_PATH`;do kill $i;rm $AGSAPI_PIDS_DIR_PATH/$i; done;
