#!/usr/bin/python
# coding: utf-8

import os
import re
import json

def make_code_table(types_equipements_dir_path):
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

def add_libelle_to_json_data(json_data, objet_table, code_table):
    match_it = re.finditer(r'".*?":.*?\{.*?idObjet.*?:.*?"(.*?)".*?.*?idInfo.*?:.*?"(.*?)".*?type.*?:.*?"(.*?)".*?\}', json_data, re.DOTALL)

    for match in match_it:
        nom = match.group(1)
        code = match.group(2)
        info_type = match.group(3)

        if "Alarme" in info_type:
            info_type = "Alarme"
        if "Etat" in info_type:
            info_type = "Etat"
        if "Mesure" in info_type:
            info_type = "Mesure"
        if "InfoGen" in info_type:
            info_type = "Information"
        libelle = code_table[objet_table[nom]["type"]][info_type][code]

if __name__ == '__main__':
    code_table = make_code_table("./TypesEquipements/")
    print(code_table["EM_TR"]["Alarme"]["500001"])
