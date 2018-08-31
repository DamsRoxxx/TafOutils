#!/usr/bin/python
# coding: utf-8

import logging
import csv

def filter_equipments(input_file_path, output_file_path, equipments_list_file_path):
    logging.info(
        "filter_equipments(%s, %s, %s)", 
        input_file_path, output_file_path,
        equipments_list_file_path
    )

    # Index logical names
    with open(equipments_list_file_path) as f:
        lines = f.read().splitlines()
    eqpts_set = set()
    for eqpt in lines:
        eqpts_set.add(eqpt)

    input_file = open(input_file_path, "r")
    output_file = open(output_file_path, "w")

    # Keep only lines with a logical name present in indexed data
    input_csv_reader = csv.reader(input_file, delimiter=';')
    output_csv_writer = csv.writer(output_file, delimiter=';')
    for line in input_csv_reader:
        if line[0] in eqpts_set:
            output_csv_writer.writerow(line)

    input_file.close()
    output_file.close()
