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
    elif len(filesToCompare) == 3:
        pass
    else:
        logging.error("Bad number of files in the input files list [%s]", ', '.join(filesToCompare))

def indexData(fileToIndex):
    indexedData = dict()
    logging.info("Indexing data...")
    with open(fileToIndex, 'rb') as fileToIndexCSV:
            secondFileReader = csv.reader(fileToIndexCSV, delimiter=';')
            for row in secondFileReader:
                    NL 		= row[0] 
                    Code 	= row[1] 
                    Valeur	= row[2]
                    Date		= datetime.strptime(row[3], "%Y-%m-%d %H:%M:%S")
                    
                    if (Date < start) or (Date > end):
                            continue
                    
                    if not NL in indexedData:
                            indexedData[NL] = dict()
                            indexedData[NL][Code] = dict()		
                            indexedData[NL][Code][Date] = []
                    elif not Code in indexedData[NL]:
                            indexedData[NL][Code] = dict()		
                            indexedData[NL][Code][Date] = []
                    elif not Date in indexedData[NL][Code]:
                            indexedData[NL][Code][Date] = []
                    indexedData[NL][Code][Date].append(Valeur)
    return indexedData

def findInIndexedData(indexedData, nl, code, valeur, date):
        if not nl in indexedData:
                return
                
        if not code in indexedData[nl]:
                return
                
        for delay in range(-checkDelay, checkDelay + 1):
                indexedDataDate = date + timedelta(seconds=delay)
                
                if indexedDataDate in indexedData[nl][code]:
                        if valeur in indexedData[nl][code][indexedDataDate]:
                                indexedData[nl][code][indexedDataDate].remove(valeur)
                                if not indexedData[nl][code][indexedDataDate]:
                                        del indexedData[nl][code][indexedDataDate]
                                if not indexedData[nl][code]:
                                        del indexedData[nl][code]
                                if not indexedData[nl]:
                                        del indexedData[nl]
                                return indexedDataDate

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

def compare3(outputFile, firstFile, secondFile, thirdFile, startDateStr, endDateStr):
    checkDelay	= 5
    start = datetime.strptime(startDateStr, dateformat)
    end = datetime.strptime(endDateStr, dateformat)

    logging.info(datetime.now())

    with open(outputFile, 'wb') as RESFile:
            RESWriter = csv.writer(RESFile, delimiter=';')
            RESWriter.writerow(("THANL", "THACode", "THAValeur", "THATEDDate", "THAHistDate", "THAAudDate"))
            
            secondFileIndex = indexData(secondFile)
            thirdFileIndex = indexData(thirdFile)

            logging.info("Reading firstFile data...")
            with open(firstFile, 'rb') as firstFileCSV:
                    firstFileReader = csv.reader(firstFileCSV, delimiter=';')
                    for firstFileRow in firstFileReader:
                            nl 		= firstFileRow[0] 
                            code 		= firstFileRow[1] 
                            valeur		= firstFileRow[2]
                            date		= datetime.strptime(firstFileRow[3], "%Y-%m-%d %H:%M:%S")

                            if (date < start) or (date > end):
                                    continue

                            secondFileDate		= findInIndexedData(secondFileIndex, nl, code, valeur, date)
                            thirdFileDate           = findInIndexedData(thirdFileIndex, nl, code, valeur, date)
                            if secondFileDate:
                                if thirdFileDate:
                                    RESWriter.writerow((nl, code, valeur, date, secondFileDate, thirdFileDate))
                                else:
                                    RESWriter.writerow((nl, code, valeur, date, secondFileDate, None))
                            else:
                                if thirdFileDate:
                                    RESWriter.writerow((nl, code, valeur, date, None, thirdFileDate))
                                else:
                                    RESWriter.writerow((nl, code, valeur, date, None, None))
                    
            logging.info("Appending remaining secondFile data...")
            for nl in secondFileIndex.keys():
                    for code in secondFileIndex[nl].keys():
                            for date in secondFileIndex[nl][code].keys():
                                    for valeur in secondFileIndex[nl][code][date]:
                                        thirdFileDate = findInIndexedData(thirdFileIndex, nl, code, valeur, date)
                                        if thirdFileDate:
                                            RESWriter.writerow((nl, code, valeur, None, date, thirdFileDate))
                                        else:
                                            RESWriter.writerow((nl, code, valeur, None, date, None))

            logging.info("Appending remaining thirdFile data...")
            for nl in thirdFileIndex.keys():
                    for code in thirdFileIndex[nl].keys():
                            for date in thirdFileIndex[nl][code].keys():
                                    for valeur in thirdFileIndex[nl][code][date]:
                                            RESWriter.writerow((nl, code, valeur, None, None, date))
                                    
    logging.info(datetime.now())
