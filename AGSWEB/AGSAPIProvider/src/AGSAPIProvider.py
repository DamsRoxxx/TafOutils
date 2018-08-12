#!/usr/bin/python
# coding: utf-8

from Config import *
from DBHandler import *
from JSONFormating import *
from LibellePostProcess import *
import sys
import cherrypy
import os

class AGSAPIProvider:
    def __init__(self, cfg):
        self.cfg = cfg
        # self.code_table = make_code_table("./TypesEquipements/")

        # dbh = DBHandler(self.cfg.database_name)
        # self.objet_table = dbh.make_objet_table()
        # dbh.close()

    @cherrypy.expose
    def index(self):
        return "Index page"

    # Provides JSON formated list of available names in the database
    @cherrypy.expose
    def nameslist(self):
        dbh = DBHandler(self.cfg.database_name)
        jdata = JSONFormating.format_names_list(dbh.list_names())
        dbh.close()
        return jdata

    # Provides JSON formated list of requested data
    @cherrypy.expose
    def list_name_libelle_type(self):
        dbh = DBHandler(self.cfg.database_name)
        jdata = JSONFormating.format_data_list(dbh.list_name_libelle_type())
        dbh.close()
        return jdata

    # Provides JSON formated list of requested data
    @cherrypy.expose
    def data(self, name="", type="", limit="", filter=""):
        dbh = DBHandler(self.cfg.database_name)
        jdata = JSONFormating.format_data_list(dbh.list_data(name, type, limit, filter))
        dbh.close()
        return jdata

    # Provides an easy to pars list of requested data
    @cherrypy.expose
    def lightnameslist(self, name="", type=""):
        dbh = DBHandler(self.cfg.database_name)
        names_list =  ';'.join(dbh.list_names())
        dbh.close()
        return names_list

    # Provides an easy to pars list of requested data
    @cherrypy.expose
    def lightdata(self, name="", type="", limit=""):
        dbh = DBHandler(self.cfg.database_name)
        light_data =  ';'.join(dbh.list_data(name, type, limit))
        dbh.close()
        return light_data

    @cherrypy.expose
    def descobjet(self):
        dbh = DBHandler(self.cfg.database_name)
        descobjet = dbh.make_descobjet_dict()
        dbh.close()
        return json.dumps(descobjet, sort_keys=True, indent=4)

# To allow CORS requests from localhost:8081
def CORS():
  cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"

if __name__ == '__main__':
    cfg = Config()

    # Create a file with the pid of the process for the stop script
    open(cfg.agsapi_path + "/common/pids/" + str(os.getpid()), 'a').close()

    # Allow external connections
    cherrypy.config.update({'server.socket_host': '0.0.0.0'})

    # Set up the serving port
    cherrypy.config.update({'server.socket_port': 8080})

    # Allow CORS requests from the domain specified in CORS function
    cherrypy.tools.CORS = cherrypy.Tool('before_handler', CORS)
    cherrypy.config.update({'tools.CORS.on': True})

    # Start the server
    cherrypy.quickstart(AGSAPIProvider(cfg))
