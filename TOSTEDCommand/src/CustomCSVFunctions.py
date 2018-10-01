#!/usr/bin/python
# coding: utf-8

from datetime import datetime

def sort_csv_by_date(csv, date_col, date_format):
    return sorted(csv, key=lambda row: datetime.strptime(row[date_col], date_format))

def load_csv(file_path, delimiter):
    with open(file_path, "r") as f:
        csv_lines = f.read().splitlines()
    csv = [row.split(delimiter) for row in csv_lines]
    return csv

def csv_to_csv_str(csv, delimiter):
    csv_lines = [delimiter.join(row) for row in csv]
    csv_str = "\n".join(csv_lines)
    return csv_str + "\n"

def csv_str_to_csv(csv_str, delimiter):
    csv_lines = csv_str.splitlines()
    csv = [row.split(delimiter) for row in csv_lines]
    return csv
