#!/usr/bin/python
# coding: utf-8

# VERSION : 1.0

import os
import sys
import xlrd
from xlsxwriter.workbook import Workbook
import zipfile
from datetime import datetime

FILES_TO_MERGE = ["PdC", "Staffing", "Ressources"]

def MergeSheet(booksList, sheetName, dstWorkbook):
    dstWorksheet = dstWorkbook.add_worksheet(sheetName)
    dateFormat = dstWorkbook.add_format({'num_format': 'dd/mm/yy'})
    # Write header
    sheet = booksList[0].sheet_by_index(0)
    if sheet.nrows > 0:
        rowValues = sheet.row_values(0)
        for col in range(len(rowValues)):
            dstWorksheet.write(0, col, rowValues[col], dateFormat)

    # Merge contents
    startId = 0
    for book in booksList:
        sheet = book.sheet_by_index(0)
        for row in range(1, sheet.nrows):
            rowValues = sheet.row_values(row)
            for col in range(len(rowValues)):
                dstWorksheet.write(startId + row, col, rowValues[col])
        startId += sheet.nrows - 1
    dstWorksheet.autofilter('A1:BN1')

def MergeXLSXFilesList(filesList, dst):
    workbook = Workbook(dst)

    booksList = [xlrd.open_workbook(fileToMerge) for fileToMerge in filesList]
    # MergeSheet(booksList, "Feuil1", worksheet)
    sheetNamesList = [sheet.name for sheet in booksList[0].sheets()]
    for sheetName in sheetNamesList:
        MergeSheet(booksList, sheetName, workbook)
    
    workbook.close()

def MergeFiles(filesList, directory):
    mergingDst = os.path.join(directory, os.path.basename(filesList[0]).split(" ")[0] + " " + os.path.basename(directory) + ".xlsx")
    print("Merging {} to {}".format(filesList, mergingDst))
    if len(filesList) > 0:
        MergeXLSXFilesList(filesList, mergingDst)

def ListDir(sourceDirectory):
    dirList = []
    for element in os.listdir(sourceDirectory):
        absolutePath = os.path.join(sourceDirectory, element)
        if os.path.isdir(absolutePath):
            dirList.append(absolutePath)
    return dirList

def MergeDirFiles(dirList):
    for fileToMerge in FILES_TO_MERGE:
        filesList = []
        for dir in dirList:
            for presentFile in os.listdir(dir):
                if fileToMerge in presentFile:
                    absoluteFilePath = os.path.join(dir, presentFile)
                    if os.path.isfile(absoluteFilePath):
                        filesList.append(absoluteFilePath)

        if len(filesList) > 0:
            MergeFiles(filesList, os.path.dirname(dirList[0]))

def RecursivelyMerge(sourceDirectory):
    dirList = ListDir(sourceDirectory)
    if len(dirList) == 0:
        return
        
    for directory in ListDir(sourceDirectory):
        RecursivelyMerge(directory)
        MergeDirFiles(ListDir(directory))

def MergeSVM(sourceDirectory):
    RecursivelyMerge(sourceDirectory)
    MergeDirFiles(ListDir(sourceDirectory))

def zipfolder(foldername, filename, includeEmptyDIr=True):   
    empty_dirs = []  
    zip = zipfile.ZipFile(filename, 'w', zipfile.ZIP_DEFLATED)  
    for root, dirs, files in os.walk(foldername):  
        empty_dirs.extend([dir for dir in dirs if os.listdir(os.path.join(root, dir)) == []])  
        for name in files:  
            zip.write(os.path.join(root ,name))  
        if includeEmptyDIr:  
            for dir in empty_dirs:  
                zif = zipfile.ZipInfo(os.path.join(root, dir) + "/")  
                zip.writestr(zif, "")  
        empty_dirs = []  
    zip.close() 

def PdC2Qlik(pdcFile):
    print("Creating QlikPdC.xlsx")
    workbook = Workbook("QlikPdC.xlsx")
    worksheet = workbook.add_worksheet("QlikPdC")

    book = xlrd.open_workbook(pdcFile)
    sheet = book.sheet_by_index(0)

    worksheet.write(0, 0, "PDCNumAffaire")
    worksheet.write(0, 1, "PDCIntituleAffaire")
    worksheet.write(0, 2, "PDCEntite")
    worksheet.write(0, 3, "PDCGroupe")
    worksheet.write(0, 4, "PDCCompetences")
    worksheet.write(0, 5, "PDCCharge")
    worksheet.write(0, 6, "PDCDate")

    dateFormat = workbook.add_format({'num_format': 'dd/mm/yy'})
    writeRowId = 1
    for row in range(1, sheet.nrows):
        rowValues = sheet.row_values(row)
        for i in range(60):
            if rowValues[6 + i] == 0 or sheet.cell_type(row, 6 + i) in (xlrd.XL_CELL_EMPTY, xlrd.XL_CELL_BLANK):
                continue
            for j in range(6):
                worksheet.write(writeRowId, j, rowValues[j])
            worksheet.write(writeRowId, 6, rowValues[6 + i])
            worksheet.write(writeRowId, 6, sheet.row_values(0)[6 + i], dateFormat)
            writeRowId += 1
    workbook.close()

def Staffing2Qlik(staffingFile):
    print("Creating QlikStaffing.xlsx")
    workbook = Workbook("QlikStaffing.xlsx")
    worksheet = workbook.add_worksheet("QlikStaffing")

    book = xlrd.open_workbook(staffingFile)
    sheet = book.sheet_by_index(0)

    worksheet.write(0, 0, "PDCNumAffaire")
    worksheet.write(0, 1, "PDCIntituleAffaire")
    worksheet.write(0, 2, "PDCEntite")
    worksheet.write(0, 3, "PDCGroupe")
    worksheet.write(0, 4, "PDCCompetences")
    worksheet.write(0, 5, "PDCStaffing")
    worksheet.write(0, 6, "PDCAPW")
    worksheet.write(0, 7, "PDCCharge")
    worksheet.write(0, 8, "PDCDate")

    dateFormat = workbook.add_format({'num_format': 'dd/mm/yy'})
    writeRowId = 1
    for row in range(1, sheet.nrows):
        rowValues = sheet.row_values(row)
        for i in range(12):
            if rowValues[9 + i] == 0 or sheet.cell_type(row, 9 + i) in (xlrd.XL_CELL_EMPTY, xlrd.XL_CELL_BLANK):
                continue
            for j in range(9):
                worksheet.write(writeRowId, j, rowValues[j])
            worksheet.write(writeRowId, 9, rowValues[9 + i])
            worksheet.write(writeRowId, 8, sheet.row_values(0)[9 + i], dateFormat)
            writeRowId += 1
    workbook.close()

if __name__ == '__main__':
    directory = ""
    for element in os.listdir("."):
        if os.path.isdir(element):
            directory = element
    if directory == "":
        print("Missing directory")
        sys.exit(0)

    print("Saving zip file")
    date = datetime.strftime(datetime.now(), "%Y-%m-%d_%H-%M-%S")
    zipfolder(directory, "{}_{}.zip".format(os.path.basename(os.path.normpath(directory)), date))

    MergeSVM(directory)
    dirName = os.path.basename(os.path.normpath(directory))
    PdC2Qlik(os.path.join(directory, "PdC " + dirName + ".xlsx"))
    Staffing2Qlik(os.path.join(directory, "Staffing " + dirName + ".xlsx"))
