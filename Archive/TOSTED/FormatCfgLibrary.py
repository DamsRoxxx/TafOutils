#!/usr/bin/python
# coding: utf-8

import sys

if len(sys.argv) != 3:
    print("Usage: {} [CFG_LIBRARY_XML] [OUTPUT_CSV]".format(__file__))
    sys.exit(0)

cfg_library_file = sys.argv[1]
output_csv = sys.argv[2]

with open(cfg_library_file, "r") as f:
    cfg_library_lines = f.read().splitlines()

# <station nomLogique="nl_328_1001_9976" nomAPB="obep_noeud_SUCYBN">
# <equipement nomLogique="M2E_P-MIOR-000003267_136021000AINLC570" type="NDS"/>

output_csv_str = ""
for line in cfg_library_lines:
    if "<station" in line:
        station = line.split('"')[1]
        apb = line.split('"')[3]
    if "<equip" in line:
        nom_logique = line.split('"')[1]
        type = line.split('"')[3]
        output_csv_str += "{};{};{};{}\n".format(station, apb, nom_logique, type)

output_csv_str = "APBNdS;APBObep;APBNL;APBType\n" + output_csv_str
with open(output_csv, "w") as f:
    f.write(output_csv_str)
