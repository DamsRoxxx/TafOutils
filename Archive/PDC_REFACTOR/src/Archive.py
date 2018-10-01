#!/usr/bin/python
# coding: utf-8

import os
import zipfile
from datetime import datetime
import logging

def zip_directory(foldername, filename, include_empty_dir=True):   
    empty_dirs = []  
    zip = zipfile.ZipFile(filename, 'w', zipfile.ZIP_DEFLATED)  
    for root, dirs, files in os.walk(foldername):  
        empty_dirs.extend([dir for dir in dirs if os.listdir(os.path.join(root, dir)) == []])  
        for name in files:  
            zip.write(os.path.join(root ,name))  
        if include_empty_dir:  
            for dir in empty_dirs:  
                zif = zipfile.ZipInfo(os.path.join(root, dir) + "/")  
                zip.writestr(zif, "")  
        empty_dirs = []  
    zip.close() 

def archive_directory(directory):
    date = datetime.strftime(datetime.now(), "%Y-%m-%d_%H-%M-%S")
    output_file_path = os.path.normpath(os.path.join(directory, "..", "{}_{}.zip".format(os.path.basename(directory), date)))

    logging.info("archive_directory(%s, %s)", directory, output_file_path)

    zip_directory(directory, output_file_path)
