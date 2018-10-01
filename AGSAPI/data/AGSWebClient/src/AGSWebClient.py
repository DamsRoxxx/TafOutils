#!/usr/bin/python
# coding: utf-8

import cherrypy
import os

class AGSWebClient:
    # Index page of the server
    @cherrypy.expose
    def index(self):
        with open("agswebclient.html", "r") as html_file:
            html = html_file.read()
        return html

if __name__ == '__main__':
    # Create a file with the pid of the process for the stop script
    open(os.environ['AGSAPI_PIDS_DIR_PATH'] + "/" + str(os.getpid()), 'a').close()

    # Allow external connections
    cherrypy.config.update({'server.socket_host': '0.0.0.0'})

    # Set up the serving port
    cherrypy.config.update({'server.socket_port': 8086})

    # Current dir as data dir for JavaScript files
    cherrypy.config.update({'tools.staticdir.on': True})
    cherrypy.config.update({'tools.staticdir.dir': os.path.abspath(".")})

    # Start the server
    cherrypy.quickstart(AGSWebClient())
