#!/usr/bin/python
# coding: utf-8

import logging
import os
import csv
from datetime import datetime
from StringIO import StringIO
from Common import *

# Create a CSV file from the log files present in the input_dir_path filtering
# data that are not between start_date_str and end_date_str. The date format is
# "YYYY-MM-DD hh:mm:ss"
def extract_tos_logs(input_dir_path, output_file_path, start_date_str, end_date_str):
    logging.info(
        "extract_tos_logs(%s, %s, %s, %s)", 
        input_dir_path, output_file_path,
        start_date_str, end_date_str
    )
    
    # Converts dates to datetime format
    tos_date_format = "%d/%m/%Y %H:%M:%S"
    start_date = datetime.strptime(start_date_str, DATE_FORMAT)
    end_date = datetime.strptime(end_date_str, DATE_FORMAT)

    # Prepare tmp CSV file in a StringIO
    tmp_file = StringIO()
    tmp_csv_writer = csv.writer(tmp_file, delimiter=';')

    # Merge alarms presents in log files to the output CSV
    for log_filename in os.listdir(input_dir_path):
        # Get file path
        file_path = os.path.join(input_dir_path, log_filename)
        logging.info("Processing %s", file_path)

        # Load log file lines
        with open(file_path, "r") as log_file:
            log_file_lines = log_file.readlines()

        # Write alarms lines to the tmp file
        for line in log_file_lines:
            if "NOTIF 'alarme'" in line:
                # Extract timestamp
                timestamp_str = line.split("horodate=<")[1][:-2]

                # Check if timestamp is between start_date and end_date
                timestamp = datetime.strptime(timestamp_str, tos_date_format)
                if timestamp >= start_date and timestamp <= end_date:
                    # Extract needed data
                    equipment = line.split("quipement=<")[1].split(">")[0]
                    code = line.split("code=<")[1].split(">")[0]
                    value = line.split("active=<")[1].split(">")[0]

                    # Write extracted data to the tmp file
                    tmp_csv_writer.writerow([equipment, code, value, datetime.strftime(timestamp, DATE_FORMAT)])

    # Sort extracted lines
    sorted_lines = sort_csv_file_by_dates(tmp_file, 3)

    # We don't need the tmp file anymore
    tmp_file.close()

    # Write sorted lines to the output CSV
    write_csv_data(sorted_lines, output_file_path)
