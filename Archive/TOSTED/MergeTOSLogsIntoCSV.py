#!/usr/bin/python
# coding: utf-8

###################################################################################################
# Ce script fusionne tous les fichiers DriverNDSI présents dans le répertoire passé en argument en
# un fichier TOS.csv contenant les données utiles pour effectuer les analyses.
#
# Usage: ./MergeTOSLogsIntoCSV.py [DIRECTORY] [START_DATE] [END_DATE]
# DIRECTORY: Répertoire contenant les fichiers DriverNDSI.
###################################################################################################

import sys
import os
from datetime import datetime
from subprocess import call

print("MergeTOSLogsIntoCSV")

# Vérfication du nombre d'arguments de la ligne de commande
if len(sys.argv) != 4:
    print("Usage: {} [DIRECTORY] [START_DATE] [END_DATE]".format(__file__))
    sys.exit(0)

# Récupération des arguments de la ligne de commande
driver_dir = sys.argv[1] + "/"
start_date_str = sys.argv[2]
end_date_str = sys.argv[3]

print("DRIVER DIR: " + driver_dir)
print("START DATE: " + start_date_str)
print("END DATE: " + end_date_str)

# Formatage des dates filtrées
date_format = "%Y-%m-%d %H:%M:%S"
start_date = datetime.strptime(start_date_str, date_format)
end_date = datetime.strptime(end_date_str, date_format)

csv_delimiter = ';'
csv_str = ""

for log_file in sorted(os.listdir(driver_dir)):
    absolute_log_file_path = driver_dir + log_file
    print("Traitement de " + absolute_log_file_path)
    with open(absolute_log_file_path, "r") as f:
        lines = f.readlines()
    for line in lines:
        if "NOTIF 'alarme'" in line:
            equipement = line.split("quipement=<")[1].split(">")[0]
            horodatage = line.split("horodate=<")[1][:-2]
            valeur = line.split("active=<")[1].split(">")[0]
            datetime_horodatage = datetime.strptime(horodatage, "%d/%m/%Y %H:%M:%S")
            horodatage = datetime.strftime(datetime_horodatage, "%Y-%m-%d %H:%M:%S")
            code = line.split("code=<")[1].split(">")[0]
            if datetime_horodatage >= start_date and datetime_horodatage <= end_date:
                csv_line = "{}.{}.{}.{}".replace('.', csv_delimiter).format(
                equipement, code, valeur, horodatage)
                csv_str += csv_line + '\n'

with open("TOS.csv", "w") as f:
    f.write(csv_str)
