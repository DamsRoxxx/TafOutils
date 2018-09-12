#!/usr/bin/python
# coding: utf-8

import logging
import csv
import os
from xlsxwriter.workbook import Workbook
from CustomCSVFunctions import *

def tosted_to_xlsx(input_file_path, output_file_path):
    logging.info("tosted_to_xlsx(%s, %s)", input_file_path, output_file_path)
    workbook = Workbook(output_file_path)
    worksheet = workbook.add_worksheet(os.path.basename(output_file_path)[:-4])
    header_list = ["Moteur", "TOSTEDNL", "Code", "Valeur", "TEDDate", "TOSDate"]
    col = 0
    for header_name in header_list:
        worksheet.write(0, col, header_name)
        col += 1

    row = 1
    csv = load_csv(input_file_path, ";")
    for line in csv:
        col = 0
        for data in line:
            worksheet.write(row, col, data)
            col += 1
        row += 1

    workbook.close()
