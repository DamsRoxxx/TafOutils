#!/usr/bin/python
# coding: utf-8

import shutil
import logging
import os

def merge_files(output_file, input_dir):
    logging.info(
        "merge_files(%s, %s)", 
        output_file, input_dir
    )
    files_list = [os.path.join(input_dir, f) for f in os.listdir(input_dir)]
    with open(output_file, "w") as output_file_obj:
        for file_path in files_list:
            with open(file_path, "r") as file_obj:
                shutil.copyfileobj(file_obj, output_file_obj)

