#!/usr/bin/python
# coding: utf-8

import sys
import csv
from collections import defaultdict

# Supprime les lignes identiques selon toutes les colonnes excepte l'horodatage
def RemoveDuplicates(inputCSV, outputCSV):
    inputCSVFile = open(inputCSV, "rb")
    outputCSVFile = open(outputCSV, "wb")

    inputCSVReader = csv.reader(inputCSVFile, delimiter=';')
    outputCSVWriter = csv.writer(outputCSVFile, delimiter=';')

    removeCounter = 0
    lastRow = defaultdict(lambda: defaultdict(str))
    for row in inputCSVReader:
        nomLogique = row[0]
        code = row[1]
        valeur = row[2]
        horodatage = row[3]
        if nomLogique in lastRow:
            if lastRow[nomLogique][code] == valeur:
                removeCounter += 1
                # print(row)
            else:
                outputCSVWriter.writerow((nomLogique, code, valeur, horodatage))
        else:
            outputCSVWriter.writerow((nomLogique, code, valeur, horodatage))

        lastRow[nomLogique][code] = valeur

    print("Removed: {}".format(removeCounter))

    inputCSVFile.close()
    outputCSVFile.close()

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: {} [INPUT_CSV] [OUTPUT_CSV]".format(__file__))
        sys.exit(0)

    inputCSV = sys.argv[1] 
    outputCSV = sys.argv[2]

    RemoveDuplicates(inputCSV, outputCSV)
