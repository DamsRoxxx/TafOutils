#!/usr/bin/python
# coding: utf-8

import os
from subprocess import call

# cd src
os.chdir("src")

# Appropriate command depending on the OS
if os.name == "nt":
    CMD = ".\\auto.py"
else:
    CMD = "./auto.py"

# Run auto.py
call(CMD, shell=True)
