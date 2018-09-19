#!/usr/bin/python
# coding: utf-8

from collections import defaultdict
import re

def index_stations(cfg_library_file_path):
    stations_index = defaultdict(lambda: defaultdict(str))

    with open(cfg_library_file_path) as f:
        cfg_library_lines = f.readlines()

    current_station = "NONE"
    for line in cfg_library_lines:
        if "<station" in line:
            m = re.search('nomLogique="(.*?)" nomAPB="(.*?)"', line)
            logical_name = m.group(1)
            apb_name = m.group(2)
            current_station = apb_name
        elif "<equipement" in line:
            m = re.search('nomLogique="(.*?)" type="(.*?)"', line)
            logical_name = m.group(1)
            type = m.group(2)
            stations_index[current_station][logical_name] = type

    return stations_index

def in_same_station(stations_index, logical_name_a, logical_name_b):
    for station in stations_index:
        if (logical_name_a in stations_index[station]) and (logical_name_b in stations_index[station]):
            return True
    return False

def generate_cas4(cfg_library_file_path, parc_file_path):
    stations_index = index_stations(cfg_library_file_path)

if __name__ == '__main__':
    cfg_library_file_path = "./cfgLibrairie.xml"
    parc_file_path = "./parc.csv"
    generate_cas4(cfg_library_file_path, parc_file_path)
