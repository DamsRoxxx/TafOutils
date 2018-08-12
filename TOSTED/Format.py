#!/usr/bin/python
# coding: utf-8

import sys
from datetime import datetime
from CustomCSVFunctions import *

def format_audace_preformated(input_csv_str, output_csv_file_path, start_date, end_date):
    print("Formatage")
    csv_file_lines = input_csv_str.split("\n")
    if csv_file_lines[-1] == "":
        csv_file_lines.pop()

    date_format = "%Y-%m-%d %H:%M:%S"
    output_csv = ""
    for line in csv_file_lines:
        row = line.split(";")
        nom_logique = row[0]
        detectee = row[1]
        disparue = row[2]
        code = row[3]
        bad_code = False
        try:
            int(code)
        except ValueError:
            bad_code = True
        if bad_code:
            continue
        if detectee != "":
            datetime_detectee = datetime.strptime(detectee, date_format)
            if (datetime_detectee >= start_date) and (datetime_detectee <= end_date):
                output_csv += "{};{};{};{}\n".format(nom_logique, code, "1", detectee)
        if disparue != "":
            datetime_disparue = datetime.strptime(disparue, date_format)
            if (datetime_disparue >= start_date) and (datetime_disparue <= end_date):
                output_csv += "{};{};{};{}\n".format(nom_logique, code, "0", disparue)

    print("Tri du fichier CSV")
    csv = csv_str_to_csv(output_csv, ";")
    csv = sort_csv_by_date(csv, 3, date_format)
    sorted_csv_str = csv_to_csv_str(csv, ";")
    with open(output_csv_file_path, "w") as f:
        f.write(sorted_csv_str)
