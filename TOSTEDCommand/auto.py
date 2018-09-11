#!/usr/bin/python
# coding: utf-8

import os
from subprocess import call
import logging
import shutil

def merge_files(output_file, files_list):
    with open(output_file, "w") as output_file_obj:
        for file_path in files_list:
            with open(file_path, "r") as file_obj:
                shutil.copyfileobj(file_obj, output_file_obj)

def runcmd(cmd):
    call(cmd, shell=True)

RESULT_DIR = "RESULT"
DATA_DIR = "RES"
START_DATE = "2018-08-02 00:00:01"
END_DATE = "2018-08-05 23:59:59"

if os.name == "nt":
    CMD = ".\TOSTEDCommand.py"
else:
    CMD = "./TOSTEDCommand.py"

# TED_INPUT = os.path.join(DATA_DIR, "TED")
TOS_INPUT = os.path.join(DATA_DIR, "TOS")
HISTO_TED_INPUT = os.path.join(DATA_DIR, "HISTO_TED")
# AUDACE_TED_INPUT = os.path.join(DATA_DIR, "AUDACE_TED")
# AUDACE_TOS_INPUT = os.path.join(DATA_DIR, "AUDACE_TOS")

PARC_INPUT = os.path.join(DATA_DIR, "parc.csv")

# TED
# runcmd('{} --ted -i {} -o RAW_TED.csv --start-date "{}" --end-date "{}"'.format(CMD, TED_INPUT, START_DATE, END_DATE))

# TOS
runcmd('{} --extract-driver-ndsi -i {} -o ExtractedDriverNDSI'.format(CMD, TOS_INPUT))
runcmd('{} --tos -i ExtractedDriverNDSI -o RAW_TOS.csv --start-date "{}" --end-date "{}"'.format(CMD, START_DATE, END_DATE))

# HistoTED
print("Merge files")
merge_files("HISTO_TED.csv", [os.path.join(HISTO_TED_INPUT, file_path) for file_path in os.listdir(HISTO_TED_INPUT)])
runcmd('{} --hted -i {} -o RAW_HISTO_TED.csv --start-date "{}" --end-date "{}" --parc {}'.format(CMD, "HISTO_TED.csv", START_DATE, END_DATE, PARC_INPUT))

# AudaceTED
# runcmd('{} --ated -i {} -o RAW_AUDACE_TED.csv --start-date "{}" --end-date "{}"'.format(CMD, AUDACE_TED_INPUT, START_DATE, END_DATE))

# AudaceTOS
# runcmd('{} --atos -i {} -o RAW_AUDACE_TOS.csv --start-date "{}" --end-date "{}"'.format(CMD, AUDACE_TOS_INPUT, START_DATE, END_DATE))

# Filter CAS4
# runcmd('{} --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_TED.csv -o FILTERED_TED.csv')
runcmd('{} --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_TOS.csv -o FILTERED_TOS.csv'.format(CMD))
runcmd('{} --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_HISTO_TED.csv -o FILTERED_HISTO_TED.csv'.format(CMD))
# runcmd('{} --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_AUDACE_TED.csv -o FILTERED_AUDACE_TED.csv')
# runcmd('{} --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_AUDACE_TOS.csv -o FILTERED_AUDACE_TOS.csv')

# Remove TOS duplicates
runcmd('{} --remove-duplicates -i FILTERED_TOS.csv -o NO_DUPLICATES_TOS.csv'.format(CMD))

# Compare TOSTED
runcmd('{} --compare -i FILTERED_HISTO_TED.csv NO_DUPLICATES_TOS.csv --start-date "{}" --end-date "{}" -o TOSTED.csv'.format(CMD, START_DATE, END_DATE))

# Compare TEDHISTAUD
# runcmd('{} --compare -i FILTERED_TED.csv FILTERED_HISTO_TED.csv FILTERED_AUDACE_TED.csv --start-date "{}" --end-date "{}" -o TEDHISTAUD.csv'.format(CMD, START_DATE, END_DATE))
