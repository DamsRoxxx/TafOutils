#!/usr/bin/python
# coding: utf-8

from pprint import pprint, pformat
import logging
import os
import sys
from ExcelHandler import *

def generic_merge_files(files_list, output_file):
    writer = ExcelWriter(output_file)
    writer.add_sheet(os.path.basename(output_file).strip('.xlsx'))
    writer.bind_sheet(0)
    # Write header
    writer.concat(files_list[0], end_point=0)
    # Concatenate contents
    for file in files_list:
        writer.concat(file, start_point=1)
    writer.close()
    

# Merge a list of PdC files
def merge_pdc_files(files_list, output_file):
    logging.info("merge_pdc_files(%s, %s)", pformat(files_list), output_file)
    generic_merge_files(files_list, output_file)

# Merge a list of Ressources files
def merge_ressources_files(files_list, output_file):
    logging.info("merge_ressources_files(%s, %s)", pformat(files_list), output_file)
    generic_merge_files(files_list, output_file)

# Merge a list of Staffing files
def merge_staffing_files(files_list, output_file):
    logging.info("merge_staffing_files(%s, %s)", pformat(files_list), output_file)
    generic_merge_files(files_list, output_file)

# List directories in dir_path
def list_dir(dir_path):
    try:
        return [
            os.path.join(dir_path, path)
            for path in os.listdir(dir_path)
            if os.path.isdir(os.path.join(dir_path, path))
        ]
    except OSError:
        logging.error("%s is not a directory", dir_path)
        sys.exit(0)
    
def recursive_merge(dir_path, merge_options):
    logging.info("recursive_merge(%s, %s)", dir_path, format(merge_options))

    def merge_subdirs_files(dir, merge_options):
        logging.info("merge_subdirs_files(%s)", dir)

        subdirs_list = list_dir(dir)

        # Do nothing if there is no subdirs
        if len(list_dir(dir)) == 0:
            return

        for file_key in merge_options:
            files_to_merge = []
            for subdir in subdirs_list:
                for subdir_file in os.listdir(subdir):
                    if file_key in subdir_file:
                        files_to_merge.append(os.path.join(subdir, subdir_file))
            merge_options[file_key](files_to_merge, os.path.join(dir, file_key + ' ' + os.path.basename(dir) + ".xlsx"))
        
    def recursive_merge_aux(dir_path, merge_options):
        # Recursion
        subdirs_list = list_dir(dir_path)
        for subdir in subdirs_list:
            recursive_merge_aux(subdir, merge_options)

        # Actions
        for dir in subdirs_list:
            merge_subdirs_files(dir, merge_options)

    recursive_merge_aux(dir_path, merge_options)
    merge_subdirs_files(dir_path, merge_options)
