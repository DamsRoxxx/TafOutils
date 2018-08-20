#!/usr/bin/python
# coding: utf-8

import sys
import csv
from collections import defaultdict

def HistoTOSToCSV(inputCSV, outputCSV):
    # Indexation de la table des noms logiques
    nomLogiqueIndex = defaultdict(lambda: defaultdict(lambda: defaultdict(str)))
    with open("TableNomLogiqueHistoTOS.csv", "rb") as nomLogiqueTableFile:
        nomLogiqueTableCSVReader = csv.reader(nomLogiqueTableFile, delimiter=';')
        nomLogiqueTableCSVReader.next() # Ignore la premiere ligne
        for row in nomLogiqueTableCSVReader:
            nomLogique = unicode(row[0], "utf-8")
            libelle = unicode(row[1], "utf-8")
            mnemonique = unicode(row[5], "utf-8")
            nomStation = unicode(row[3], "utf-8")
            nomLogiqueIndex[mnemonique][libelle][nomStation] = nomLogique

    # Indexation de la table des codes
    codeIndex = defaultdict(lambda: defaultdict(str))
    with open("TableCodeHistoTOS.csv", "rb") as codeTableFile:
        codeTableCSVReader = csv.reader(codeTableFile, delimiter=';')
        codeTableCSVReader.next() # Ignore la premiere ligne
        for row in codeTableCSVReader:
            mnemonique = unicode(row[0], "utf-8")
            libelle1 = unicode(row[4], "utf-8")
            code = unicode(row[2], "utf-8")
            codeIndex[mnemonique][libelle1] = code

    # Formatage
    inputCSVFile = open(inputCSV, "rb")
    outputCSVFile = open(outputCSV, "wb")
    inputCSVReader = csv.reader(inputCSVFile, delimiter=';')
    outputCSVWriter = csv.writer(outputCSVFile, delimiter=';')

    inputCSVReader.next() # Ignore la premiere ligne
    for row in inputCSVReader:
        evenement = row[7]
        horodatage = unicode(row[0][:-2], "ISO-8859-1")
        typeEqpt = unicode(row[2], "ISO-8859-1")
        libelleEqpt = unicode(row[3], "ISO-8859-1")
        libelleAlarme = unicode(row[6], "ISO-8859-1")
        nomStation = unicode(row[1], "ISO-8859-1")
        nomLogique = nomLogiqueIndex[typeEqpt][libelleEqpt][nomStation]
        code = codeIndex[typeEqpt][libelleAlarme]

        # Ne pas traiter la ligne si il ne s'agit pas d'un debut ou d'une fin d'alarme
        if evenement == "Mise en attente d'une IDP":
            valeur = 1
        elif evenement == "Fin d'une IDP":
            valeur = 0
        else:
            print(';'.join([str(nomLogique), str(code), str(evenement), str(horodatage)]))
            continue

        outputCSVWriter.writerow((nomLogique, code, valeur, horodatage))

    inputCSVFile.close()
    outputCSVFile.close()

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: {} [INPUT_CSV] [OUTPUT_CSV]".format(__file__))
        sys.exit(0)
        
    inputCSV = sys.argv[1]
    outputCSV = sys.argv[2]

    HistoTOSToCSV(inputCSV, outputCSV)
