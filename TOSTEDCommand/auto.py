#!/usr/bin/python
# coding: utf-8

import os
from subprocess import call

def runcmd(cmd):
    call(cmd, shell=True)

DATA_DIR = "RES_03-08_05-08/"
START_DATE = "2018-08-03 00:00:01"
END_DATE = "2018-08-05 23:59:59"

TED_INPUT = os.path.join(DATA_DIR, "TED")
TOS_INPUT = os.path.join(DATA_DIR, "TOS")
HISTO_TED_INPUT = os.path.join(os.path.join(DATA_DIR, "HISTO_TED"), "HISTO_TED.csv")
# AUDACE_TED_INPUT = 
# AUDACE_TOS_INPUT = 

PARC_INPUT = os.path.join(DATA_DIR, "parc.csv")

runcmd('tosted --ted -i {} -o RAW_TED.csv --start-date "{}" --end-date "{}"'.format(TED_INPUT, START_DATE, END_DATE))
runcmd('tosted --tos -i {} -o RAW_TOS.csv --start-date "{}" --end-date "{}"'.format(TOS_INPUT, START_DATE, END_DATE))
runcmd('tosted --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_TED.csv -o FILTERED_TED.csv')
runcmd('tosted --filter cas_4_Liste_EQ_CONFORME_20180706.csv -i RAW_TOS.csv -o FILTERED_TOS.csv')
runcmd('tosted --remove-duplicates -i FILTERED_TOS.csv -o NO_DUPLICATES_TOS.csv')

runcmd('tosted --hted -i {} -o RAW_HISTO_TED.csv --start-date "{}" --end-date "{}" --parc {}'.format(HISTO_TED_INPUT, START_DATE, END_DATE, PARC_INPUT))

