#!/usr/bin/python
# coding: utf-8

import logging
import cherrypy
from DBHandler import DBHandler
from Logger import *
from FormatToJSON import *
from pprint import pprint
from collections import defaultdict
import json
import os
from LibelleSupport import make_code_to_libelle_dict

class AGSAPIProvider:
    def __init__(self, code_to_libelle_dict):
        self.db_name = os.environ['AGSAPI_DB']
        self.nom_to_type_dict = dict()
        self.code_to_libelle_dict = code_to_libelle_dict

    @cherrypy.expose
    def index(self):
        return "Index page"

    @cherrypy.expose
    def descobjet(self):
        db_handler = DBHandler(self.db_name)
        raw_descobjet_dict = format_to_dict(db_handler.get_descobjet_list())

        # Specific format for DescObjet
        descobjet_dict = defaultdict(lambda: defaultdict(lambda: defaultdict(lambda: defaultdict(str))))
        for obj in raw_descobjet_dict:
            groupe = raw_descobjet_dict[obj]["idGroupe"]
            espace = raw_descobjet_dict[obj]["idEspace"]
            libelle = raw_descobjet_dict[obj]["libelle"]
            nom = raw_descobjet_dict[obj]["nom"]
            type = raw_descobjet_dict[obj]["type"]

            descobjet_dict[groupe][espace][libelle]["nom"] = nom
            descobjet_dict[groupe][espace][libelle]["type"] = type

            self.nom_to_type_dict[nom] = type

        descobjet_json = json.dumps(descobjet_dict, sort_keys=True, indent=4)
        db_handler.close()
        return descobjet_json

    @cherrypy.expose
    def data(self, NomLogique=None, DataType=None):
        if NomLogique == None or DataType == None:
            return "{}"
        else:
          db_handler = DBHandler(self.db_name)
          dds_data_dict = format_to_dict(db_handler.get_dds_data_list(NomLogique, DataType))
          for key in dds_data_dict:
              dds_data_dict[key]["dataType"] = DataType

              try:
                idObjet = dds_data_dict[key]["idObjet"]
                idInfo = dds_data_dict[key]["idInfo"]
                dds_data_dict[key]["libelle"] = self.code_to_libelle_dict[self.nom_to_type_dict[idObjet]][DataType][idInfo]
              except:
                dds_data_dict[key]["libelle"] = "Inconnu"
          dds_data_json = format_to_json(dds_data_dict)
          db_handler.close()
          return dds_data_json

def CORS():
    cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"

if __name__ == '__main__':
    init_logger()

    # Create a file with the pid of the process for the stop script
    open(os.environ['AGSAPI_PIDS_DIR_PATH'] + "/" + str(os.getpid()), 'a').close()

    # Allow external connections
    cherrypy.config.update({'server.socket_host': '0.0.0.0'})

    # Set up the serving port
    cherrypy.config.update({'server.socket_port': 8085})

    # Allow CORS requests from the domain specified in CORS function
    cherrypy.tools.CORS = cherrypy.Tool('before_handler', CORS)
    cherrypy.config.update({'tools.CORS.on': True})

    # Start the server
    code_to_libelle_dict = make_code_to_libelle_dict("./TypesEquipements/")
    cherrypy.quickstart(AGSAPIProvider(code_to_libelle_dict))
