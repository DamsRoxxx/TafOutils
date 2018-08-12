#!/usr/bin/python
# coding: utf-8

import xlrd
import os
import sys
from ReplaceCode import *
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
            type_eqpt = sheet.row_values(row)[2]
            nom_logique = sheet.row_values(row)[3]
            detectee = sheet.row_values(row)[5]
            disparue = sheet.row_values(row)[7]
            code = str(sheet.row_values(row)[8])[:-2]
            csv_str += "{};{};{};{};{};{}\n".format(type_eqpt, nom_logique, detectee, disparue, "", code)

header_line = "TYPE;NOM_LOGIQUE;DETECTEE;DISPARUE;CODE_TED;CODE_TOS"
csv_str = header_line + "\n" + csv_str

csv_str = replace_codes(csv_str)

# Remove first col
csv_str_lines = csv_str.split("\n")
csv_str_lines = [";".join(line.split(";")[1:]) for line in csv_str_lines]
csv_str = "\n".join(csv_str_lines)

format_audace_preformated(csv_str, "Audace_TOS.csv", start_date, end_date)
