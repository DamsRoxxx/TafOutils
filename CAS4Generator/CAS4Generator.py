#!/usr/bin/python
# coding: utf-8

import re
import csv
import logging
from collections import defaultdict

PARC_INDEX = defaultdict(lambda: defaultdict(str))
STATIONS_INDEX = defaultdict(lambda: defaultdict(str))
REFTEC_INDEX = dict()

def index_parc(parc_file_path):
    with open(parc_file_path) as f:
        csv_reader = csv.reader(f, delimiter=';')

        for row_values in csv_reader:
            if len(row_values) < 24:
                continue

            logical_name = row_values[23]
            PARC_INDEX[logical_name]['PRODUCTION'] = row_values[13]
            PARC_INDEX[logical_name]['SUPERVISABLE'] = row_values[15]
            PARC_INDEX[logical_name]['FUNCTIONNAL_FATHER'] = row_values[19]

            REFTEC_INDEX[row_values[0]] = logical_name

def index_stations(cfg_library_file_path):
    with open(cfg_library_file_path) as f:
        cfg_library_lines = f.readlines()

    current_station = "NONE"
    for line in cfg_library_lines:
        if "<station" in line:
            m = re.search('nomLogique="(.*?)" nomAPB="(.*?)"', line)
            logical_name = m.group(1) # Unused
            apb_name = m.group(2)
            current_station = apb_name
        elif "<equipement" in line:
            m = re.search('nomLogique="(.*?)" type="(.*?)"', line)
            logical_name = m.group(1)
            type = m.group(2)
            STATIONS_INDEX[current_station][logical_name] = type

def in_same_station(logical_name_a, logical_name_b):
    for station in STATIONS_INDEX:
        if (logical_name_a in STATIONS_INDEX[station]) and (logical_name_b in STATIONS_INDEX[station]):
            return True
    return False

def in_production_and_supervisable(logical_name):
    if PARC_INDEX[logical_name]['PRODUCTION'] != 2 and PARC_INDEX[logical_name]['SUPERVISABLE'] != 2:
        return True
    return False

def has_functionnal_father(logical_name):
    if PARC_INDEX[logical_name]['FUNCTIONNAL_FATHER'] != "" and PARC_INDEX[logical_name]['FUNCTIONNAL_FATHER'] != "\N":
        return True
    return False

def is_not_pci(station, equipment):
    if STATIONS_INDEX[station][equipment] != "PC_I" and STATIONS_INDEX[station][equipment] != "NDS":
        return True
    return False

def get_functionnal_father(logical_name):
    return REFTEC_INDEX[PARC_INDEX[logical_name]['FUNCTIONNAL_FATHER']]

def is_cas4(equipment):
    logging.info("Equipement: " + equipment)
    if in_production_and_supervisable(equipment):
        logging.info("En production et supervisable")
        if has_functionnal_father(equipment):
            functionnal_father = get_functionnal_father(equipment)
            logging.info("Père fonctionnel: " + functionnal_father)
            if equipment == functionnal_father:
                logging.info("Equipement = Père fonctionnel -> NON-CAS4")
                return False
            if is_cas4(functionnal_father):
                logging.info("Père fonctionnel CAS4")
                if in_same_station(equipment, functionnal_father):
                    logging.info("Dans la même station -> CAS4")
                    return True
                else:
                    logging.info("Pas dans la même station -> NON-CAS4")
                    return False
            else:
                logging.info("Père fonctionnel NON-CAS4")
                return False
        else:
            logging.info("Pas de père fonctionnel -> CAS4")
            return True
    else:
        logging.info("NON-CAS4")
        return False

def reftec_id_to_logical_name(id_reftec):
    return REFTEC_INDEX[id_reftec]

def generate_cas4(cfg_library_file_path, parc_file_path):
    index_stations(cfg_library_file_path)
    index_parc(parc_file_path)
    for station in STATIONS_INDEX:
        for equipment in STATIONS_INDEX[station]:
            if is_not_pci(station, equipment) and is_cas4(equipment):
                print(equipment)

if __name__ == '__main__':
    log_file_path = "log"
    logging.FileHandler(log_file_path, "w")
    logging.basicConfig(
        filename=log_file_path,
        format='%(levelname)s :: %(message)s',
        level=logging.DEBUG
    )

    cfg_library_file_path = "./cfgLibrairie.xml"
    parc_file_path = "./parc.csv"
    generate_cas4(cfg_library_file_path, parc_file_path)
