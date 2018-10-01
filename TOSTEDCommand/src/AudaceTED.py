#!/usr/bin/python
# coding: utf-8

import xlrd
import os
import sys
from datetime import datetime
from Format import *
from Common import *
import logging

def convert_value_to_str(value):
    if isinstance(value, unicode):
        return  str(value.encode("UTF-8"))
    return  str(value)

def audace_ted(input_dir_path, output_csv_path, start_date_str, end_date_str):
    logging.info(
        "audace_ted(%s, %s, %s, %s)", 
        input_dir_path, output_csv_path,
        start_date_str, end_date_str
    )

    start_date = datetime.strptime(start_date_str, DATE_FORMAT)
    end_date = datetime.strptime(end_date_str, DATE_FORMAT)

    csv_str = ""
    for xl_file_name in os.listdir(input_dir_path):
        xl_file_path = os.path.join(input_dir_path, xl_file_name)
        logging.info("Traitement de " + xl_file_path)
        if xl_file_name.split(".")[1] == "xls":
            book = xlrd.open_workbook(xl_file_path)
            sheet = book.sheet_by_name("Alarmes")
            for row in range(6, sheet.nrows):
                type_eqpt = convert_value_to_str(sheet.row_values(row)[2])
                nom_logique = convert_value_to_str(sheet.row_values(row)[3])
                detectee = convert_value_to_str(sheet.row_values(row)[6])
                disparue = convert_value_to_str(sheet.row_values(row)[10])
                code = str(sheet.row_values(row)[8])[:-2]
                csv_str += "{};{};{};{}\n".format(nom_logique, detectee, disparue, code)

    format_audace_preformated(csv_str, output_csv_path, start_date, end_date)
