#!/usr/bin/python
# coding: utf-8


import csv
import time
from datetime import datetime, date, time, timedelta
import sys

if len(sys.argv) != 6:
    print("Usage: {} [TED_FILE] [TOS_FILE] [START_DATE] [END_DATE] [OUTPUT_CSV]".format(__file__))
    sys.exit(0)
    

dateformat = "%Y-%m-%d %H:%M:%S"
tosDelay	= 5
TEDFile 	= sys.argv[1]
TOSFile 	= sys.argv[2]
start 	= datetime.strptime(sys.argv[3], dateformat)
end 	= datetime.strptime(sys.argv[4], dateformat)
TOSTEDFile 	= sys.argv[5]

TOSIndex = dict()

print datetime.now()


def findInTOS(nl, code, valeur, date):
	if not nl in TOSIndex:
		return
		
	if not code in TOSIndex[nl]:
		return
		
	for delay in range(0, tosDelay):
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

with open(TOSTEDFile, 'wb') as RESFile:
	RESWriter = csv.writer(RESFile, delimiter=';')
	
	print "Indexing TOSCANE data..."
	with open(TOSFile, 'rb') as TOSCSV:
		TOSReader = csv.reader(TOSCSV, delimiter=';')
		for TOSRow in TOSReader:
			TOSNL 		= TOSRow[0] 
			TOSCode 	= TOSRow[1] 
			TOSValeur	= TOSRow[2]
			TOSDate		= datetime.strptime(TOSRow[3], "%Y-%m-%d %H:%M:%S")
			
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

	print "Reading TED data..."
	with open(TEDFile, 'rb') as TEDCSV:
		TEDReader = csv.reader(TEDCSV, delimiter=';')
		for TEDRow in TEDReader:
			nl 			= TEDRow[0] 
			code 		= TEDRow[1] 
			valeur		= TEDRow[2]
			date		= datetime.strptime(TEDRow[3], "%Y-%m-%d %H:%M:%S")

			if (date < start) or (date > end):
				continue

			tosDate		= findInTOS(nl, code, valeur, date)
			if tosDate:
				RESWriter.writerow((0, nl, code, valeur, date, tosDate))
			else:
				RESWriter.writerow((1, nl, code, valeur, date, None))
		
	print "Appending remaining TOS data..."
	for nl in TOSIndex.keys():
		for code in TOSIndex[nl].keys():
			for date in TOSIndex[nl][code].keys():
				for valeur in TOSIndex[nl][code][date]:
					RESWriter.writerow((2,nl, code, valeur, None, date))
				
print datetime.now()
