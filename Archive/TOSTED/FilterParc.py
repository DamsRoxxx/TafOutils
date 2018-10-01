#!/usr/bin/python
# coding: utf-8

import sys

def try_get(values, index):
    try:
        return values[index]
    except IndexError:
        return ""

if len(sys.argv) != 3:
    print("Usage: {} [PARC_FILE] [OUTPUT_CSV]".format(__file__))
    sys.exit(0)

parc_file = sys.argv[1]
output_csv = sys.argv[2]

with open(parc_file, "r") as f:
    parc_lines = f.read().splitlines()

csv_str = ""
for line in parc_lines:
    values = line.split(";")

    code_bm = try_get(values, 3)
    id_lieu = try_get(values, 12)
    pere_fonctionnel = try_get(values, 19)
    nom_logique = try_get(values, 23) 
    type_ags = try_get(values, 22)

    csv_line = ";".join([code_bm, id_lieu, pere_fonctionnel, nom_logique, type_ags])
    csv_str += csv_line + "\n"

csv_str = "PARCBM;PARCUG;PARCPere;PARCNL;PARCTypeAGS\n" + csv_str
with open(output_csv, "w") as f:
    f.write(csv_str)
