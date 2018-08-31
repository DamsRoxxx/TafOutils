#!/usr/bin/python
# coding: utf-8

import logging
import csv
import time
from datetime import datetime, date, time, timedelta

TOSIndex = dict()
tosDelay = 5

def findInTOS(nl, code, valeur, date):
    if not nl in TOSIndex:
        return
        
    if not code in TOSIndex[nl]:
        return
        
    for delay in range(-tosDelay, tosDelay + 1):
        tosDate = date + timedelta(seconds=delay)
        
        if tosDate in TOSIndex[nl][code]:
            if valeur in TOSIndex[nl][code][tosDate]:
                TOSIndex[nl][code][tosDate].remove(valeur)
                if not TOSIndex[nl][code][tosDate]:
                    del TOSIndex[nl][code][tosDate]
                if not TOSIndex[nl][code]:
                    del TOSIndex[nl][code]
                if not TOSIndex[nl]:
                    del TOSIndex[nl]
                return tosDate

def compare(outputFile, filesToCompare, startDateStr, endDateStr):
    logging.info("compare(%s, %s, %s, %s)", outputFile, filesToCompare, startDateStr, endDateStr)

    if len(filesToCompare) == 2:
        compare2(outputFile, filesToCompare[0], filesToCompare[1], startDateStr, endDateStr)
    else:
        logging.error("Bad number of files in the input files list [%s]", ', '.join(filesToCompare))

def compare2(outputFile, tedFile, tosFile, startDateStr, endDateStr):
    dateformat = "%Y-%m-%d %H:%M:%S"
    TEDFile = tedFile
    TOSFile = tosFile
    start = datetime.strptime(startDateStr, dateformat)
    end = datetime.strptime(endDateStr, dateformat)
    TOSTEDFile = outputFile


    with open(TOSTEDFile, 'w') as RESFile:
        RESWriter = csv.writer(RESFile, delimiter=';')
        
        
        with open(TOSFile, 'rb') as TOSCSV:
            TOSReader = csv.reader(TOSCSV, delimiter=';')
            for TOSRow in TOSReader:
                TOSNL         = TOSRow[0] 
                TOSCode     = TOSRow[1] 
                TOSValeur    = TOSRow[2]
                TOSDate        = datetime.strptime(TOSRow[3], "%Y-%m-%d %H:%M:%S")
                
                if (TOSDate < start) or (TOSDate > end):
                    continue
                
                if not TOSNL in TOSIndex:
                    TOSIndex[TOSNL] = dict()
                    TOSIndex[TOSNL][TOSCode] = dict()        
                    TOSIndex[TOSNL][TOSCode][TOSDate] = []
                elif not TOSCode in TOSIndex[TOSNL]:
                    TOSIndex[TOSNL][TOSCode] = dict()        
                    TOSIndex[TOSNL][TOSCode][TOSDate] = []
                elif not TOSDate in TOSIndex[TOSNL][TOSCode]:
                    TOSIndex[TOSNL][TOSCode][TOSDate] = []
                TOSIndex[TOSNL][TOSCode][TOSDate].append(TOSValeur)

        
        with open(TEDFile, 'rb') as TEDCSV:
            TEDReader = csv.reader(TEDCSV, delimiter=';')
            for TEDRow in TEDReader:
                nl             = TEDRow[0] 
                code         = TEDRow[1] 
                valeur        = TEDRow[2]
                date        = datetime.strptime(TEDRow[3], "%Y-%m-%d %H:%M:%S")

                if (date < start) or (date > end):
                    continue

                tosDate        = findInTOS(nl, code, valeur, date)
                if tosDate:
                    RESWriter.writerow((0, nl, code, valeur, date, tosDate))
                else:
                    RESWriter.writerow((1, nl, code, valeur, date, None))
            
        
        for nl in TOSIndex.keys():
            for code in TOSIndex[nl].keys():
                for date in TOSIndex[nl][code].keys():
                    for valeur in TOSIndex[nl][code][date]:
                        RESWriter.writerow((2,nl, code, valeur, None, date))
