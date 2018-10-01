#!/usr/bin/python
# coding: utf-8

import json
from Logger import log

def format_to_dict(data_list):
    ignored_keys = ["ack"]
    data_dict = dict()
    for i in range(len(data_list)):
        data_dict[str(i)] = dict()
        for line in data_list[i].strip().splitlines():
            line_split = line.strip().split(":")
            key = line_split[0]
            value = line_split[1].strip()
            if key not in ignored_keys:
                data_dict[str(i)][key] = value.strip('"')
    return data_dict

def format_to_json(data_dict):
    return json.dumps(data_dict, indent=4)
