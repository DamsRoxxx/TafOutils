#!/usr/bin/python
# coding: utf-8

# Welcome in hell...

import json
import re
from DBHandler import *
from LibellePostProcess import *

code_table = make_code_table("./TypesEquipements/")

dbh = DBHandler(os.environ['AGSAPI_DB'])
objet_table = dbh.make_objet_table()
dbh.close()

class JSONFormating:

    # Take a list of names and convert it to JSON format
    @staticmethod
    def format_names_list(names_list):
        json_names = ""
        id = 0
        for name in names_list:
            json_names += '"{0}":'.format(id) + '"{0}"'.format(name) + ","
            id += 1
        json_names = "{" + json_names[:-1] + "}"

        return json_names

        # Enable to pretty print JSON nameslist server side
        # parsed = json.loads(json_names)
        # cleaned_json_names = json.dumps(parsed, indent=4, sort_keys=False)

        # return cleaned_json_names

    # Take a database "data" entry and convert it to a JSON object
    @staticmethod
    def data_to_json_object(data):
        # data = data.replace(' ', '')
        # print data
        lines = data.split("\n")
        json_data = ""

        # idCodePublicFirst (Very slow code)
        # for i in range(len(lines)):
        #   if "idCodePublic" in lines[i]:
        #     codePublicIndex = i
        #     break
        # lines.insert(0, lines.pop(codePublicIndex))

        for line in lines:
            if line == "":
                continue

            if not "libelle" in line:
              line = line.replace(' ', '')
            split = line.split(":")

            if split[0] == "libelle":
                # print (split[1])
                # Remove front spaces
                space_counter = 0
                for i in range(len(split[1])):
                    if split[1][i] == " ":
                        space_counter += 1
                    else:                                                                       
                        break
                split[1] = split[1][space_counter:]
              
            if split[1] == "":
                json_data += '"{0}"'.format(split[0]) + ': "null",'
            else:
                if not '"' in split[1]:
                    json_data += '"{0}":"{1}",'.format(split[0], split[1])
                else:
                    json_data += '"{0}":{1},'.format(split[0], split[1])

        json_data = "{" + json_data[:-1] + "}"
        return json_data

    # Take a list of data and convert is to JSON format
    @staticmethod
    def format_data_list(data_list):
        json_data = ""
        id = 0
        for data in data_list:
            # Add libelle
            try:
                match = re.search(r'.*idObjet: "(.*?)".*', data)
                id_objet = match.group(1)

                match = re.search(r'.*idInfo: (.*?)\n', data, re.DOTALL)
                id_info = match.group(1)

                match = re.search(r'.*type: (.*?)\n', data, re.DOTALL)
                info_type = match.group(1)

                if "Alarme" in info_type:
                    info_type = "Alarme"
                if "Etat" in info_type:
                    info_type = "Etat"
                if "Mesure" in info_type:
                    info_type = "Mesure"
                if "InfoGen" in info_type:
                    info_type = "Information"

                libelle = code_table[objet_table[id_objet]["type"]][info_type][id_info].replace(":", "-")
            except:
              libelle = "Inconnu"

            data += '\nlibelle: "%s"' % libelle
            
            try:
                json_data += '"{0}":'.format(id) + '{0}'.format(JSONFormating.data_to_json_object(data)) + ","
            except:
                json_data += '"{0}":'.format(id) + '"BAD DATA FORMAT",'

            id += 1
        json_data = "{" + json_data[:-1] + "}"

        return json_data

        # Enable to pretty print JSON data server side
        # parsed = json.loads(json_data)
        # cleaned_json_data = json.dumps(parsed, indent=4, sort_keys=False)

        # return cleaned_json_data
