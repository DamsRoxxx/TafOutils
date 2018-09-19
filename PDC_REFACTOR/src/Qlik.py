#!/usr/bin/python
# coding: utf-8

import logging
import os
import xlrd
from xlsxwriter.workbook import Workbook

def pdc_to_qlik(pdc_file_path, output_file_path):

    logging.info("pdc_to_qlik(%s, %s)", pdc_file_path, output_file_path)

    workbook = Workbook(output_file_path)
    worksheet = workbook.add_worksheet(os.path.basename(output_file_path).strip(".xlsx"))

    book = xlrd.open_workbook(pdc_file_path)
    sheet = book.sheet_by_index(0)

    worksheet.write(0, 0, "PDCNumAffaire")
    worksheet.write(0, 1, "PDCIntituleAffaire")
    worksheet.write(0, 2, "PDCEntite")
    worksheet.write(0, 3, "PDCGroupe")
    worksheet.write(0, 4, "PDCCompetences")
    worksheet.write(0, 5, "PDCCharge")
    worksheet.write(0, 6, "PDCDate")

    date_format = workbook.add_format({'num_format': 'dd/mm/yy'})
    write_row_id = 1
    for row in range(1, sheet.nrows):
        row_values = sheet.row_values(row)
        for i in range(60):
            if row_values[6 + i] == 0 or sheet.cell_type(row, 6 + i) in (xlrd.XL_CELL_EMPTY, xlrd.XL_CELL_BLANK):
                continue
            for j in range(6):
                worksheet.write(write_row_id, j, row_values[j])
            worksheet.write(write_row_id, 5, row_values[6 + i])
            worksheet.write(write_row_id, 6, sheet.row_values(0)[6 + i], date_format)
            write_row_id += 1
    workbook.close()

def staffing_to_qlik(staffing_file_path, output_file_path):
    logging.info("staffing_to_qlik(%s, %s)", staffing_file_path, output_file_path)

    workbook = Workbook(output_file_path)
    worksheet = workbook.add_worksheet(os.path.basename(output_file_path).strip(".xlsx"))

    book = xlrd.open_workbook(staffing_file_path)
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

    date_format = workbook.add_format({'num_format': 'dd/mm/yy'})
    write_row_id = 1
    for row in range(1, sheet.nrows):
        row_values = sheet.row_values(row)
        for i in range(12):
            if row_values[9 + i] == 0 or sheet.cell_type(row, 9 + i) in (xlrd.XL_CELL_EMPTY, xlrd.XL_CELL_BLANK):
                continue

            c = 0
            for j in [0, 1, 2, 3, 4, 6, 7]:
                worksheet.write(write_row_id, c, row_values[j])
                c += 1

            worksheet.write(write_row_id, 7, row_values[9 + i])
            worksheet.write(write_row_id, 8, sheet.row_values(0)[9 + i], date_format)
            write_row_id += 1
    workbook.close()
