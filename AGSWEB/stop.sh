#!/bin/bash

PIDS_DIR_PATH=./common/pids
for i in `ls $PIDS_DIR_PATH`;do kill $i;rm $PIDS_DIR_PATH/$i; done;
