#!/usr/bin/python
# coding: utf-8

import sys
import csv
from datetime import datetime

def FormatHistoTED(inputCSVPath, outputCSVPath, startDate, endDate, parcCSVPath):
    dateFormat = "%Y-%m-%d %H:%M:%S"

    inputCSVFile = open(inputCSVPath, "rb")
    inputCSVReader = csv.reader(inputCSVFile, delimiter=';')
    inputCSVReader = sorted(inputCSVReader, key=lambda row: datetime.strptime(row[1], dateFormat))

    outputCSVFile = open(outputCSVPath, "wb")
    outputCSVWriter = csv.writer(outputCSVFile, delimiter=';')

    with open(parcCSVPath) as parcCSVFile:
        parcIndexedData = dict()
        parcCSVReader = csv.reader(parcCSVFile, delimiter=';')
        for row in parcCSVReader:
            # Do not index lines with empty nom logique
            if len(row) < 24:
                continue

            parcIdReftec = row[0]
            parcNomLogique = row[23]
            parcIndexedData[parcIdReftec] = parcNomLogique

    for row in inputCSVReader:
        valeur = row[0]
        horodatageStr = row[1]
        idReftec = row[3]
        code = row[4]

        # Skip if code is not an int
        if not code.isdigit():
            continue
        
        # Skip if horodatage is not in our range
        horodatage = datetime.strptime(horodatageStr, dateFormat)
        if (horodatage < startDate) or (horodatage > endDate):
            continue

        valeur = '1' if valeur == 'D' else '0'
        outputCSVWriter.writerow((parcIndexedData[idReftec], code, valeur, horodatageStr))

    inputCSVFile.close()
    outputCSVFile.close()

if __name__ == '__main__':
    if len(sys.argv) != 6:
        print("Usage: {} [INPUT_CSV] [OUTPUT_CSV] [START_DATE] [END_DATE] [PARC_CSV]".format(__file__))
        sys.exit(0)

    inputCSVPath = sys.argv[1]
    outputCSVPath = sys.argv[2]

    dateFormat = "%Y-%m-%d %H:%M:%S"
    startDate = datetime.strptime(sys.argv[3], dateFormat)
    endDate = datetime.strptime(sys.argv[4], dateFormat)

    parcCSVPath = sys.argv[5]

    FormatHistoTED(inputCSVPath, outputCSVPath, startDate, endDate, parcCSVPath)
