#!/usr/bin/python
# coding: utf-8

import sys
import argparse
import logging

# Parse command line arguments
def parse_args():
    parser = argparse.ArgumentParser(
        description="""
        Effectuer diverses opérations ayant pour but de
        comparer les systèmes T&D et TOSCAN.
        """
    )

    parser.add_argument(
        "-i",
        "--input",
        dest="input",
        nargs="*"
    )

    parser.add_argument(
        "-o",
        "--output",
        dest="output"
    )

    parser.add_argument(
        "--start-date",
        dest="start_date",
        type=str
    )

    parser.add_argument(
        "--end-date",
        dest="end_date",
        type=str
    )

    parser.add_argument(
        "--parc",
        dest="parc"
    )

    parser.add_argument(
        "--ted",
        dest="ted",
        action="store_true",
        help="""
        Formatage des logs TED présents dans le répertoire passé en
        input (-i) dans le CSV spécifié en output (-o) en filtrant les alarmes
        en dehors des dates précisées via --start-date et --end-date
        """
    )

    parser.add_argument(
        "--tos",
        dest="tos",
        action="store_true",
        help="""
        Formatage des logs TOS présents dans le répertoire passé en
        input (-i) dans le CSV spécifié en output (-o) en filtrant les alarmes
        en dehors des dates précisées via --start-date et --end-date
        """
    )

    parser.add_argument(
        "--hted",
        dest="hted",
        action="store_true",
        help="""
        Formatage du fichier HISTO_TED passé en input (-i) dans le CSV spécifié
        en output (-o) en filtrant les alarmes en dehors des dates précisées
        via --start-date et --end-date
        """
    )

    parser.add_argument(
        "--filter",
        dest="filter",
        metavar="EQUIPMENTS_LIST_FILE",
        help="""
        Filtre le fichier précisé en input (-i) avec les équipements présents
        dans le fichier précisé en --filter et enregistre le résultat dans le fichier
        d'output (-o)
        """
    )

    parser.add_argument(
        "--remove-duplicates",
        dest="remove_duplicates",
        action="store_true",
        help="""
        Retire les doublons de début et de fin d'alarme du fichier précisé en
        -i et enregistre le résultat dans le fichier précisé en -o
        """
    )

    parser.add_argument(
        "--compare",
        dest="compare",
        action="store_true",
        help="""
        Compare des logs CSV et les met au format Qlik.  Input files are
        specified by -i "FILE_1 FILE_2 ...". Output is specified by -o OUTPUT
        """
    )

    parser.add_argument(
        "--extract-driver-ndsi",
        dest="extract_driver_ndsi",
        action="store_true",
        help="""
        Extrait le fichier DriverNDSI de chaque fichier de log TOS présents
        dans le répertoire passé en input (-i) et les place dans le répertoire
        passé en output (-o)
        """
    )

    parser.add_argument(
        "--ated",
        dest="ated",
        action="store_true",
        help="""
        Formatage des logs AUDACE_TED présents dans le répertoire passé en
        input (-i) dans le CSV spécifié en output (-o) en filtrant les alarmes
        en dehors des dates précisées via --start-date et --end-date
        """
    )

    parser.add_argument(
        "--atos",
        dest="atos",
        action="store_true",
        help="""
        Formatage des logs AUDACE_TOS présents dans le répertoire passé en
        input (-i) dans le CSV spécifié en output (-o) en filtrant les alarmes
        en dehors des dates précisées via --start-date et --end-date
        """
    )

    parser.add_argument(
        "--merge-histo-ted",
        dest="merge_histo_ted",
        action="store_true",
        help="""
        Fusionne tous les fichiers CSV passés en -i vers le fichier CSV passé en -o
        """
    )

    parser.add_argument(
        "--xlsx",
        dest="xlsx",
        action="store_true",
        help="""
        Formate le fichier CSV donné en -i au format xlsx et enregistre le
        résultat dans le fichier précisé en -o
        """
    )

    args = parser.parse_args()

    return args

# Make sure that each argument in needed_args list is present in the command
# line arguments passed in parameter
def assert_args(args, needed_args):
    args_dict = vars(args)
    missing_args = False
    for arg in needed_args:
        if not args_dict[arg.replace('-', '_')]:
            logging.error("--{} is missing.".format(arg))
            missing_args = True
    if missing_args:
        sys.exit(0)

# Make sure that the user is not trying an impossible command
def assert_only_one_arg(args, args_to_check):
    args_dict = vars(args)
    args_counter = 0
    for arg in args_to_check:
        if args_dict[arg.replace('-', '_')]:
            args_counter += 1
    if args_counter > 1:
        logging.error("Incompatible arguments.")
        sys.exit(0)
    
