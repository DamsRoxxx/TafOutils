#!/usr/bin/python
# coding: utf-8

import csv
from xlsxwriter.workbook import Workbook

import sys

if len(sys.argv) != 2:
    print("{} [CSV_FILE]".format(__file__))
    sys.exit(0)

csvfile = sys.argv[1]

workbook = Workbook(csvfile[:-4] + '.xlsx')
worksheet = workbook.add_worksheet(csvfile[:-4])
with open(csvfile, 'rt') as f:
    reader = csv.reader(f, delimiter=";")
    for r, row in enumerate(reader):
        for c, col in enumerate(row):
            worksheet.write(r, c, col)
workbook.close()
