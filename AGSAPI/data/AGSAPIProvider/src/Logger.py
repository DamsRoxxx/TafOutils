#!/usr/bin/python
# coding: utf-8

import logging

def init_logger():
    logging.basicConfig(
        format='%(levelname)s :: %(message)s',
        level=logging.DEBUG
    )

def log(func):
    def wrapper(*args, **kwargs):
        logging.debug("%s BEGIN", func.__name__)
        result = func(*args, **kwargs)
        logging.debug("%s END", func.__name__)
        return result
    return wrapper
  
