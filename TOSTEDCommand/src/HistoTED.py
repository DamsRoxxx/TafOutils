#!/usr/bin/python
# coding: utf-8

import logging
import sys
import csv
from datetime import datetime
from Common import *

# Format the HISTO_TED.csv file passed in input
# /!\ The parc.csv file to pass in parameter is the raw parc.csv file
def histo_ted(input_csv_path, output_csv_path, start_date_str, end_date_str, parc_csv_path):
    logging.info(
        "histo_ted(%s, %s, %s, %s, %s)", 
        input_csv_path, output_csv_path,
        start_date_str, end_date_str, parc_csv_path
    )

    start_date = datetime.strptime(start_date_str, DATE_FORMAT)
    end_date = datetime.strptime(end_date_str, DATE_FORMAT)

    input_csv_file = open(input_csv_path, "r")
    sorted_lines = sort_csv_file_by_dates(input_csv_file, 1)

    output_csv_file = open(output_csv_path, "w")
    output_csv_writer = csv.writer(output_csv_file, delimiter=';')

    with open(parc_csv_path) as parc_csv_file:
        parc_indexed_data = dict()
        parc_csv_reader = csv.reader(parc_csv_file, delimiter=';')
        for row in parc_csv_reader:
            # Do not index lines with empty logical name
            if len(row) < 24:
                continue

            parc_reftec_id = row[0]
            parc_logical_name = row[23]
            parc_indexed_data[parc_reftec_id] = parc_logical_name

    for row in sorted_lines:
        value = row[0]
        timestamp_str = row[1]
        reftec_id = row[3]
        code = row[4]

        # Skip if code is not an int
        if not code.isdigit():
            continue
        
        # Skip if timestamp is not in our range
        timestamp = datetime.strptime(timestamp_str, DATE_FORMAT)
        if (timestamp < start_date) or (timestamp > end_date):
            continue

        value = '1' if value == 'D' else '0'
        output_csv_writer.writerow((parc_indexed_data[reftec_id], code, value, timestamp_str))

    input_csv_file.close()
    output_csv_file.close()
