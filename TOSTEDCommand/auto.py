#!/usr/bin/python
# coding: utf-8

import os
from subprocess import call
import logging

# CONFIG
RESULT_DIR = "RESULTS"
DATA_DIR = "DATA"
START_DATE = "2018-08-02 00:00:01"
END_DATE = "2018-08-05 23:59:59"

# Call a shell command
def runcmd(cmd):
    call(cmd, shell=True)

# Appropriate command call depending on the OS
if os.name == "nt":
    CMD = ".\TOSTEDCommand.py"
else:
    CMD = "./TOSTEDCommand.py"

# $DATA_DIR subdirs/files paths
DATA_TOS_DIR_PATH = os.path.join(DATA_DIR, "TOS")
DATA_HISTO_TED_DIR_PATH = os.path.join(DATA_DIR, "HISTO_TED")
DATA_PARC_FILE_PATH = os.path.join(DATA_DIR, "parc.csv")
DATA_CAS4_FILE_PATH = os.path.join(DATA_DIR, "cas4.csv")

# $RESULT_DIR subdirs/files paths
RESULT_DRIVER_NDSI_DIR_PATH = os.path.join(RESULT_DIR, "TOS", "DriverNDSI")
RESULT_TOS_LOG_FILE_PATH = os.path.join(RESULT_DIR, "TOS", "TOS_LOG.csv")
RESULT_RAW_HISTO_TED_LOG_FILE_PATH = os.path.join(RESULT_DIR, "HISTO_TED", "RAW_HISTO_TED_LOG.csv")
RESULT_HISTO_TED_LOG_FILE_PATH = os.path.join(RESULT_DIR, "HISTO_TED", "HISTO_TED_LOG.csv")
RESULT_CAS4_HISTO_TED_LOG_FILE_PATH = os.path.join(RESULT_DIR, "HISTO_TED", "CAS4_HISTO_TED_LOG.csv")
RESULT_CAS4_TOS_LOG_FILE_PATH = os.path.join(RESULT_DIR, "TOS", "CAS4_TOS_LOG.csv")
RESULT_NO_DUPLICATED_CAS4_TOS_LOG_FILE_PATH = os.path.join(RESULT_DIR, "TOS", "NO_DUPLICATED_CAS4_TOS_LOG.csv")
RESULT_TOSTED_CSV_FILE_PATH = os.path.join(RESULT_DIR, "TOSTED.csv")
RESULT_TOSTED_XLSX_FILE_PATH = os.path.join(RESULT_DIR, "TOSTED.xlsx")

# Create $RESULT_DIR and subdirs if they don't exist
if not os.path.exists(RESULT_DIR):
    os.mkdir(RESULT_DIR)
subdirs_list = ["TOS", "HISTO_TED", "STATS"]
for subdir in subdirs_list:
    subdir_path = os.path.join(RESULT_DIR, subdir)
    if not os.path.exists(subdir_path):
        os.mkdir(subdir_path)

# Extract DriverNDSI from $DATA_DIR/TOS to $RESULT_DIR/DriverNDSI
runcmd('{} --extract-driver-ndsi -i {} -o {}'.format(CMD, DATA_TOS_DIR_PATH, RESULT_DRIVER_NDSI_DIR_PATH))

# Parse $RESULT_DIR/TOS/DriverNDSI to create $RESULT_DIR/TOS/TOS_LOG.csv
runcmd('{} --tos -i {} -o {} --start-date "{}" --end-date "{}"'.format(CMD, RESULT_DRIVER_NDSI_DIR_PATH, RESULT_TOS_LOG_FILE_PATH, START_DATE, END_DATE))

# Merge all files from $DATA_DIR/HISTO_TED to $RESULT_DIR/HISTO_TED/HISTO_TED_LOG.csv
runcmd('{} --merge-histo-ted -i {} -o {}'.format(CMD, DATA_HISTO_TED_DIR_PATH, RESULT_RAW_HISTO_TED_LOG_FILE_PATH))

# Format $RESULT_DIR/RAW_HISTO_TED_LOG.csv to $RESULT_DIR/HISTO_TED_LOG.csv
runcmd('{} --hted -i {} -o {} --start-date "{}" --end-date "{}" --parc {}'.format(
    CMD, RESULT_RAW_HISTO_TED_LOG_FILE_PATH, RESULT_HISTO_TED_LOG_FILE_PATH, START_DATE, END_DATE, DATA_PARC_FILE_PATH
))

# Filter $RESULT_DIR/TOS/TOS_LOG.csv CAS4 and generate $RESULT_DIR/TOS/CAS4_TOS_LOG.csv
runcmd('{} --filter {} -i {} -o {}'.format(CMD, DATA_CAS4_FILE_PATH, RESULT_TOS_LOG_FILE_PATH, RESULT_CAS4_TOS_LOG_FILE_PATH))

# Filter $RESULT_DIR/HISTO_TED/HISTO_TED_LOG.csv CAS4 and generate $RESULT_DIR/HISTO_TED/CAS4_HISTO_TED_LOG.csv
runcmd('{} --filter {} -i {} -o {}'.format(CMD, DATA_CAS4_FILE_PATH, RESULT_HISTO_TED_LOG_FILE_PATH, RESULT_CAS4_HISTO_TED_LOG_FILE_PATH))

# Remove duplicates from $RESULT_DIR/TOS/CAS4_TOS_LOG.csv and generate $RESULT_DIR/TOS/NO_DUPLICATED_CAS4_TOS_LOG.csv
runcmd('{} --remove-duplicates -i {} -o {}'.format(CMD, RESULT_CAS4_TOS_LOG_FILE_PATH, RESULT_NO_DUPLICATED_CAS4_TOS_LOG_FILE_PATH))

# Generate TOSTED.csv
runcmd('{} --compare -i {} -o {} --start-date "{}" --end-date "{}"'.format(
    CMD, RESULT_CAS4_HISTO_TED_LOG_FILE_PATH + ' ' + RESULT_NO_DUPLICATED_CAS4_TOS_LOG_FILE_PATH, RESULT_TOSTED_CSV_FILE_PATH, START_DATE, END_DATE
))

# Format $RESULT_DIR/TOSTED.csv to $RESULT_DIR/TOSTED.xlsx
runcmd('{} --xlsx -i {} -o {}'.format(CMD, RESULT_TOSTED_CSV_FILE_PATH, RESULT_TOSTED_XLSX_FILE_PATH))
