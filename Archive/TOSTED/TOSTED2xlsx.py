#!/usr/bin/python
# coding: utf-8

import csv
from xlsxwriter.workbook import Workbook
from CustomCSVFunctions import *

import sys

if len(sys.argv) != 2:
    print("{} [CSV_FILE]".format(__file__))
    sys.exit(0)

csvfile = sys.argv[1]

workbook = Workbook(csvfile[:-4] + '.xlsx')
worksheet = workbook.add_worksheet(csvfile[:-4])
header_list = ["Moteur", "TOSTEDNL", "Code", "Valeur", "TEDDate", "TOSDate"]
col = 0
for header_name in header_list:
    worksheet.write(0, col, header_name)
    col += 1

row = 1
csv = load_csv(csvfile, ";")
for line in csv:
    col = 0
    for data in line:
        worksheet.write(row, col, data)
        col += 1
    row += 1

workbook.close()
