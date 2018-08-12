#!/usr/bin/python
# coding: utf-8

import os
import sys

class Config:
    def __init__(self):
        try:
          self.database_name = os.environ['AGSAPI_DB']
          self.agsapi_path = os.environ['AGSAPI_PATH']
        except KeyError:
          print("Environment variable AGSAPI_DB is not defined make sure your"
                " starting the program from the top-level start script.")
          sys.exit(0)
