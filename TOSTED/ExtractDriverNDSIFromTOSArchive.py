#!/usr/bin/python
# coding: utf-8

####################################################################################################
# Ce script extrait les fichiers DriverNDSI de toutes les archives de log TOSCANE présentes dans le
# répertoire passé en argument.
#
# Usage: ./ExtractDriverNDSIFromTOSArchive.py [DIRECTORY]
# DIRECTORY: Répertoire contenant les fichiers de log de TOSCANE au format tar.gz
####################################################################################################

from subprocess import call
import os
import sys

print("ExtractDriverNDSIFromTOSArchive")

# Vérfication du nombre d'arguments de la ligne de commande
if len(sys.argv) != 2:
    print("Usage: {} [DIRECTORY]".format(__file__))
    sys.exit(0)

# Récupération du répetoire où sont situés les archivers des logs
log_dir = sys.argv[1]

# Répertoire qui contiendra les fichiers extraits
output_dir = "Extracted_DriverNDSI"

# Pour chaque fichier .tgz ou .tar.gz on extrait le fichier DriverNDSI
# que l'on place dans le répertoire output_dir
call("mkdir -p " + output_dir, shell=True)
for archive in os.listdir(log_dir):
    if archive[-7:] == ".tar.gz" or archive[-4:] == ".tgz":
        print("Extraction de l'archive " + archive)
        call("tar -xvf {}/{} --wildcards appli/zf4/var/log/DriverNDSI_*".format(log_dir, archive), shell=True)
        call("mv appli/zf4/var/log/DriverNDSI_* {}/{}".format(output_dir, "DriverNDSI_" + archive.split(".")[0]), shell=True)
        call("rm -rf appli", shell=True)
        
