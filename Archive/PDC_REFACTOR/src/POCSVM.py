#!/usr/bin/python
# coding: utf-8

import logging
from ExcelHandler import *
from RecursiveMerge import *
from Archive import archive_directory
from Qlik import *

DIRNAME = "SVM"
DATA_DIRECTORY = os.path.join("..", DIRNAME)

if __name__ == '__main__':
    logging.basicConfig(
        # filename="POCSVM.log",
        format='%(levelname)s :: %(message)s',
        level=logging.DEBUG
    )

    archive_directory(DATA_DIRECTORY)

    merge_options = {
        "PdC": merge_pdc_files,
        "Ressources": merge_ressources_files,
        "Staffing": merge_staffing_files
    }

    recursive_merge(DATA_DIRECTORY, merge_options)

    # Generate QlikPdC.xlsx
    pdc_file_path = os.path.join(DATA_DIRECTORY, "PdC " + DIRNAME + ".xlsx")
    qlik_pdc_file_path = os.path.normpath(os.path.join(DATA_DIRECTORY, "..", "QlikPdC.xlsx"))
    pdc_to_qlik(pdc_file_path, qlik_pdc_file_path)

    # Generate QlikStaffing.xlsx
    staffing_file_path = os.path.join(DATA_DIRECTORY, "Staffing " + DIRNAME + ".xlsx")
    qlik_staffing_file_path = os.path.normpath(os.path.join(DATA_DIRECTORY, "..", "QlikStaffing.xlsx"))
    staffing_to_qlik(staffing_file_path, qlik_staffing_file_path)
