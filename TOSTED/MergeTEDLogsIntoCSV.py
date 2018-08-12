#!/usr/bin/python
# coding: utf-8

###################################################################################################
# Ce script fusionne tous les fichiers de logs présents dans le répertoire passé en argument en
# un fichier TED.csv contenant les données utiles pour effectuer les analyses.
#
# Usage: ./MergeTEDLogsIntoCSV.py [DIRECTORY] [START_DATE] [END_DATE]
# DIRECTORY: Répertoire contenant les fichiers de log TED.
###################################################################################################

import sys
import os
from datetime import datetime
from subprocess import call
from CustomCSVFunctions import *

# Vérfication du nombre d'arguments de la ligne de commande
if len(sys.argv) != 4:
    print("Usage: {} [DIRECTORY] [START_DATE] [END_DATE]".format(__file__))
    sys.exit(0)

# Récupération des arguments de la ligne de commande
logs_dir = sys.argv[1] + "/"
start_date_str = sys.argv[2]
end_date_str = sys.argv[3]

print("LOGS DIR: " + logs_dir)
print("START DATE: " + start_date_str)
print("END DATE: " + end_date_str)

# Formatage des dates filtrées
date_format = "%Y-%m-%d %H:%M:%S"
start_date = datetime.strptime(start_date_str, date_format)
end_date = datetime.strptime(end_date_str, date_format)

csv_delimiter = ';'
csv_str = ""

# Table de conversion pour la colonne "valeur"
true_values = [1, 2, 3, 4, 5, 9, 11]

for log_file in os.listdir(logs_dir):
    absolute_log_file_path = logs_dir + log_file
    print("Traitement de " + absolute_log_file_path)
    with open(absolute_log_file_path, "r") as f:
        lines = f.readlines()
    for line in lines:
        if "Evénement Alarmes" in line:
            line_split = line.split(',')
            # station = line_split[0].split("station:")[1]
            equipement = line_split[1].split(':')[1]
            horodatage = line_split[2].split(" Horodatage:")[1]
            code = line_split[3].split(':')[1]
            valeur = line_split[4].split(':')[1][:-1]
            if int(valeur) in true_values:
                valeur = 1
            else:
                valeur = 0
            datetime_horodatage = datetime.strptime(horodatage, date_format)
            if datetime_horodatage >= start_date and datetime_horodatage <= end_date:
                csv_line = "{}.{}.{}.{}".replace('.', csv_delimiter).format(
                equipement, code, valeur, horodatage)
                csv_str += csv_line + '\n'

# Tri du fichier csv produit
print("Tri du fichier CSV")
csv = csv_str_to_csv(csv_str, ";")
csv = sort_csv_by_date(csv, 3, date_format)
sorted_csv_str = csv_to_csv_str(csv, ";")

with open("TED.csv", "w") as f:
    f.write(sorted_csv_str)
