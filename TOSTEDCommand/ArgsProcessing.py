#!/usr/bin/python
# coding: utf-8

import sys
import argparse

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
        dest="input"
    )

    parser.add_argument(
        "-o",
        "--output",
        dest="output"
    )

    parser.add_argument(
        "--extract-ted-logs",
        dest="extract_ted_logs",
        action="store_true",
        help="""
        Formatage des logs TED présents dans le répertoire passé en
        input (-i) dans le CSV spécifié en output (-o) en filtrant les alarmes
        en dehors des dates précisées via --start-date et --end-date
        """
    )

    parser.add_argument(
        "--extract-tos-logs",
        dest="extract_tos_logs",
        action="store_true",
        help="""
        Formatage des logs TOS présents dans le répertoire passé en
        input (-i) dans le CSV spécifié en output (-o) en filtrant les alarmes
        en dehors des dates précisées via --start-date et --end-date
        """
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

    args = parser.parse_args()

    return args

# Make sure that each argument in needed_args list is present in the command
# line arguments passed in parameter
def assert_args(args, needed_args):
    args_dict = vars(args)
    missing_args = False
    for arg in needed_args:
        if not args_dict[arg.replace('-', '_')]:
            print("{} is missing.".format(arg.replace('-', '_').upper()))
            missing_args = True
    if missing_args:
        sys.exit(0)
