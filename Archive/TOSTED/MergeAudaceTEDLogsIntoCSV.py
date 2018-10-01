#!/usr/bin/python
# coding: utf-8

import xlrd
import os
import sys
from datetime import datetime
from Format import *

def convert_value_to_str(value):
    if isinstance(value, unicode):
        return  str(value.encode("UTF-8"))
    return  str(value)

if len(sys.argv) != 4:
    print("Usage: {} [AUDACE_LOGS_DIRECTORY] [START_DATE] [END_DATE]".format(__file__))
    sys.exit(0)

xl_files_dir = sys.argv[1] + "/"
date_format = "%Y-%m-%d %H:%M:%S"
start_date = datetime.strptime(sys.argv[2], date_format)
end_date = datetime.strptime(sys.argv[3], date_format)

csv_str = ""
for xl_file in os.listdir(xl_files_dir):
    xl_file_absolute_path = xl_files_dir + xl_file
    print("Traitement de " + xl_file_absolute_path)
    if xl_file.split(".")[1] == "xls":
        book = xlrd.open_workbook(xl_file_absolute_path)
        sheet = book.sheet_by_name("Alarmes")
        for row in range(6, sheet.nrows):
            type_eqpt = convert_value_to_str(sheet.row_values(row)[2])
            nom_logique = convert_value_to_str(sheet.row_values(row)[3])
            detectee = convert_value_to_str(sheet.row_values(row)[6])
            disparue = convert_value_to_str(sheet.row_values(row)[10])
            code = str(sheet.row_values(row)[8])[:-2]
            csv_str += "{};{};{};{}\n".format(nom_logique, detectee, disparue, code)

format_audace_preformated(csv_str, "Audace_TED.csv", start_date, end_date)
