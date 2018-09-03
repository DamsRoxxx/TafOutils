#!/usr/bin/python
# coding: utf-8

import logging
import tarfile
import shutil
import os

def driver_ndsi_members(members):
    for tarinfo in members:
        if "DriverNDSI" in tarinfo.name:
            yield tarinfo

def extract_driver_ndsi(input_dir_path, output_dir_path):
    if not os.path.exists(output_dir_path):
        os.mkdir(output_dir_path)
    for file_name in os.listdir(input_dir_path):
        file_path = os.path.join(input_dir_path, file_name)
        logging.info("Processing %s", file_path)
        tar = tarfile.open(file_path)
        tar.extractall(members=driver_ndsi_members(tar))
        tar.close()

        file_to_move = os.path.join("./appli/zf4/var/log/", os.listdir("./appli/zf4/var/log/")[0])
        new_name = os.path.join(output_dir_path, "DriverNDSI_{}".format(file_name.split('.')[0]))
        os.rename(file_to_move, new_name)
    os.removedirs("./appli/zf4/var/log/")
