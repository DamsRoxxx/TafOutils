#!/usr/bin/python
# coding: utf-8

import sys
from collections import defaultdict

def replace_codes(tos_audace_csv_str):
    
    print("Remplacement des codes audace tos")

    table_file_path = "Table.csv"
    matrice_file_path = "Matrice.csv"
    csv_delimiter = ";"

    true_type_table = {}
    matrice_table = defaultdict(lambda: defaultdict(str))
    enhanced_tos_audace_csv_str = ""

    # Construct true_type_table
    with open(table_file_path, "r") as f:
        table_lines = f.readlines()
    for line in table_lines:
        row = line[:-1].split(csv_delimiter)
        short_type_eqpt = row[0]
        type_eqpt_list = row[1]
        true_type_table[short_type_eqpt] = type_eqpt_list.split(",")

    # Construct matrice_table
    with open(matrice_file_path, "r") as f:
        matrice_lines = f.readlines()
    for i in range(1, len(matrice_lines)):
        line = matrice_lines[i]
        row = line[:-1].split(csv_delimiter)
        type_eqpt = row[0]
        code_tos = row[2]
        code_ted = row[3].replace(" ", "")
        matrice_table[type_eqpt][code_tos] = code_ted
    # -----------------------

    # Replace codes
    tos_audace_lines = tos_audace_csv_str.split("\n")
    if tos_audace_lines[-1] == "\n":
        tos_audace_lines.pop()
        
    empty_type_eqpt_counter = 0
    for i in range(1, len(tos_audace_lines)):
        line = tos_audace_lines[i]
        if line == "":
            continue
        row = line.split(csv_delimiter)
        short_type_eqpt = row[0]
        code_tos = row[5]
        if short_type_eqpt != "":
            if short_type_eqpt in true_type_table.keys():
                for type_eqpt in true_type_table[short_type_eqpt]:
                    code_ted = matrice_table[type_eqpt][code_tos]
                    if code_ted != "":
                        row[4] = code_ted
                        enhanced_tos_audace_csv_str += csv_delimiter.join(row) + "\n"
                        break
            else:
                code_ted = matrice_table[short_type_eqpt][code_tos]
                if code_ted != "":
                    row[4] = code_ted
                    enhanced_tos_audace_csv_str += csv_delimiter.join(row) + "\n"
        else:
            empty_type_eqpt_counter += 1
    # print("EMPTY TYPE LINES: " + str(empty_type_eqpt_counter))
    return enhanced_tos_audace_csv_str
    # -------------
