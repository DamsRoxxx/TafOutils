#!/usr/bin/python
# coding: utf-8

import sys

if len(sys.argv) != 3:
    print("Usage: {} [INPUT_FILE] [OUTPUT_FILE]".format(__file__))
    sys.exit(0)

inputFile = sys.argv[1]
outputFile = sys.argv[2]

with open("cas_4_Liste_EQ_CONFORME_20180706.csv") as f:
    eqptsTestCas4Lines = f.read().splitlines()

eqptsTestCas4Set = set()
for eqpt in eqptsTestCas4Lines:
    eqptsTestCas4Set.add(eqpt)

with open(inputFile) as f:
    inputFileLines = f.readlines()

filteredFileStr = ""
for line in inputFileLines:
    eqpt = line.split(";")[0]
    if eqpt in eqptsTestCas4Set:
        filteredFileStr += line

with open(outputFile, "w") as f:
    f.write(filteredFileStr)
