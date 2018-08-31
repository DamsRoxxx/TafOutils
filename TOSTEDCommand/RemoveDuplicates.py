#!/usr/bin/python
# coding: utf-8

import logging
import csv
from collections import defaultdict

def remove_duplicates(input_file_path, output_file_path):
    logging.info(
        "remove_duplicates(%s, %s)",
        input_file_path, output_file_path
    )
    input_csv = open(input_file_path, "r")
    output_csv = open(output_file_path, "w")

    input_csv_reader = csv.reader(input_csv, delimiter=';')
    output_csv_witer = csv.writer(output_csv, delimiter=';')

    remove_counter = 0
    lastRow = defaultdict(lambda: defaultdict(str))
    for row in input_csv_reader:
        logical_name = row[0]
        code = row[1]
        value = row[2]
        timestamp = row[3]

        if lastRow[logical_name][code] == value:
            remove_counter += 1
        else:
            output_csv_witer.writerow((logical_name, code, value, timestamp))

        lastRow[logical_name][code] = value


    input_csv.close()
    output_csv.close()
