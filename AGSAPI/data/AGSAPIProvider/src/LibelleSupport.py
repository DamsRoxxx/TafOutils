#!/usr/bin/python
# coding: utf-8

import os
import re

def make_code_to_libelle_dict(types_equipements_dir_path):
    # List XML files in the types_equipements_dir_path directory
    xml_files_list = os.listdir(types_equipements_dir_path)
    xml_files_list = [i for i in xml_files_list if ".xml" in i] # Keep only .xml files

    # Init empty dictionaries
    key_words_list = ["Etat", "Alarme", "Information", "Mesure"]
    libelle_table = dict()
    for xml_file in xml_files_list:
        name = xml_file[:-4]
        libelle_table[name] = dict()
        for key_word in key_words_list:
            libelle_table[name][key_word] = dict()

    # Fill dictionaries
    for xml_file in xml_files_list:
        name = xml_file[:-4]
        with open(types_equipements_dir_path + "/" + xml_file, "r") as f:
            xml = f.read()
            for key_word in key_words_list:
                regex = r'<{0}.*code="(.*?)".*libelle="(.*?)".*/>'.format(key_word) 
                match_it = re.finditer(regex, xml)
                for match in match_it:
                    libelle_table[name][key_word][match.group(1)] = match.group(2)

    return libelle_table
