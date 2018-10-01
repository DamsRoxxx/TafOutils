#!/usr/bin/python
# coding: utf-8

import os
from subprocess import call

if os.name == "posix":
    CMD = "./POCSVM.py"
else:
    CMD = ".\\POCSVM.py"

os.chdir("src")
call(CMD, shell=True)
