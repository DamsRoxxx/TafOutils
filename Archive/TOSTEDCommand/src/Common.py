#!/usr/bin/python
# coding: utf-8

from datetime import datetime
import csv

DATE_FORMAT = "%Y-%m-%d %H:%M:%S"

def sort_csv_file_by_dates(csv_file, date_col):
    csv_file.seek(0)
    csv_reader = csv.reader(csv_file, delimiter=';')
    sorted_lines = sorted(
        csv_reader,
        key=lambda line: datetime.strptime(line[date_col], DATE_FORMAT)
    )
    return sorted_lines

# input_data is a list of lines and each line is a list of columns values
def write_csv_data(input_data, output_file_path):
    with open(output_file_path, "w") as output_file:
        output_csv_writer = csv.writer(output_file, delimiter=';')
        for line in input_data:
            output_csv_writer.writerow(line)
