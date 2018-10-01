#!/usr/bin/python
# coding: utf-8

import csv
import time
from datetime import datetime, date, time, timedelta
import sys

if len(sys.argv) != 7:
    print("Usage: {} [firstFile_FILE] [secondFile_FILE] [thirdFile_FILE] [START_DATE] [END_DATE] [OUTPUT_CSV]".format(__file__))
    sys.exit(0)
    
dateformat      = "%Y-%m-%d %H:%M:%S"
checkDelay	= 5
firstFile 	= sys.argv[1]
secondFile 	= sys.argv[2]
thirdFile       = sys.argv[3]
start 	        = datetime.strptime(sys.argv[4], dateformat)
end 	        = datetime.strptime(sys.argv[5], dateformat)
outputFile 	= sys.argv[6]

print datetime.now()

def indexData(fileToIndex):
    indexedData = dict()
    print "Indexing data..."
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
		
	for delay in range(0, checkDelay):
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



with open(outputFile, 'wb') as RESFile:
	RESWriter = csv.writer(RESFile, delimiter=';')
        RESWriter.writerow(("THANL", "THACode", "THAValeur", "THATEDDate", "THAHistDate", "THAAudDate"))
	
        secondFileIndex = indexData(secondFile)
        thirdFileIndex = indexData(thirdFile)

	print "Reading firstFile data..."
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
		
	print "Appending remaining secondFile data..."
	for nl in secondFileIndex.keys():
		for code in secondFileIndex[nl].keys():
			for date in secondFileIndex[nl][code].keys():
				for valeur in secondFileIndex[nl][code][date]:
                                    thirdFileDate = findInIndexedData(thirdFileIndex, nl, code, valeur, date)
                                    if thirdFileDate:
					RESWriter.writerow((nl, code, valeur, None, date, thirdFileDate))
                                    else:
					RESWriter.writerow((nl, code, valeur, None, date, None))

	print "Appending remaining thirdFile data..."
	for nl in thirdFileIndex.keys():
		for code in thirdFileIndex[nl].keys():
			for date in thirdFileIndex[nl][code].keys():
				for valeur in thirdFileIndex[nl][code][date]:
					RESWriter.writerow((nl, code, valeur, None, None, date))
				
print datetime.now()
