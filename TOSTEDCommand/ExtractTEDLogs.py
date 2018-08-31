#!/usr/bin/python
# coding: utf-8

import logging
import os
import csv
from datetime import datetime
from StringIO import StringIO
from Common import *

# Convert TED value to 0 or 1
def convert_value(value):
    if value in ["1", "2", "3", "4", "5", "9", "11"]:
        return 1
    return 0

# Create a CSV file from the log files present in the input_dir_path filtering
# data that are not between start_date_str and end_date_str. The date format is
# "YYYY-MM-DD hh:mm:ss"
def extract_ted_logs(input_dir_path, output_file_path, start_date_str, end_date_str):
    logging.info(
        "extract_ted_logs(%s, %s, %s, %s)", 
        input_dir_path, output_file_path,
        start_date_str, end_date_str
    )
    
    # Converts dates to datetime format
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
            if "Evénement Alarmes" in line:
                line_split = line.split(',')

                # Extract timestamp
                timestamp_str = line_split[2].split(" Horodatage:")[1]

                # Check if timestamp is between start_date and end_date
                timestamp = datetime.strptime(timestamp_str, DATE_FORMAT)
                if timestamp >= start_date and timestamp <= end_date:
                    # Extract needed data
                    equipment = line_split[1].split(':')[1]
                    code = line_split[3].split(':')[1]
                    value = convert_value(line_split[4].split(':')[1][:-1])

                    # Write extracted data to the tmp file
                    tmp_csv_writer.writerow([equipment, code, value, timestamp_str])

    # Sort extracted lines
    sorted_lines = sort_csv_file_by_dates(tmp_file, 3)

    # We don't need the tmp file anymore
    tmp_file.close()

    # Write sorted lines to the output CSV
    write_csv_data(sorted_lines, output_file_path)
