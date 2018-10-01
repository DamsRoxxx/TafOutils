#!/usr/bin/python
# coding: utf-8

import logging
import os
import xlrd
from xlsxwriter.workbook import Workbook

QLIK_PDC_DATE_BEGIN = 6
QLIK_PDC_DATE_END = 65
QLIK_PDC_SKIPPED_COLUMNS = [5]

QLIK_STAFFING_DATE_BEGIN = 9
QLIK_STAFFING_DATE_END = 20
QLIK_STAFFING_SKIPPED_COLUMNS = [5]

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
    for row in range(2, sheet.nrows):
        row_values = sheet.row_values(row)
        for i in range(QLIK_PDC_DATE_BEGIN, QLIK_PDC_DATE_END + 1):
            # Empty charge
            if row_values[i] == 0 or sheet.cell_type(row, i) in (xlrd.XL_CELL_EMPTY, xlrd.XL_CELL_BLANK):
                continue

            c = 0
            for j in range(QLIK_PDC_DATE_BEGIN):
                if j in QLIK_PDC_SKIPPED_COLUMNS:
                    continue
                worksheet.write(write_row_id, c, row_values[j])
                c += 1

            worksheet.write(write_row_id, QLIK_PDC_DATE_BEGIN - len(QLIK_PDC_SKIPPED_COLUMNS), row_values[i])
            worksheet.write(write_row_id, QLIK_PDC_DATE_BEGIN - len(QLIK_PDC_SKIPPED_COLUMNS) + 1, sheet.row_values(0)[i], date_format)
            write_row_id += 1
    workbook.close()

def staffing_to_qlik(staffing_file_path, output_file_path):
    logging.info("staffing_to_qlik(%s, %s)", staffing_file_path, output_file_path)

    workbook = Workbook(output_file_path)
    worksheet = workbook.add_worksheet(os.path.basename(output_file_path).strip(".xlsx"))

    book = xlrd.open_workbook(staffing_file_path)
    sheet = book.sheet_by_index(0)

    worksheet.write(0, 0, "StaffingNumAffaire")
    worksheet.write(0, 1, "StaffingIntituleAffaire")
    worksheet.write(0, 2, "StaffingEntite")
    worksheet.write(0, 3, "StaffingGroupe")
    worksheet.write(0, 4, "StaffingCompetences")
    worksheet.write(0, 5, "StaffingStaffing")
    worksheet.write(0, 6, "StaffingAPW")
    worksheet.write(0, 7, "StaffingMoyenne")
    worksheet.write(0, 8, "StaffingCharge")
    worksheet.write(0, 9, "StaffingDate")

    date_format = workbook.add_format({'num_format': 'dd/mm/yy'})
    write_row_id = 1
    for row in range(2, sheet.nrows):
        row_values = sheet.row_values(row)
        for i in range(QLIK_STAFFING_DATE_BEGIN, QLIK_STAFFING_DATE_END + 1):
            if row_values[i] == 0 or sheet.cell_type(row, i) in (xlrd.XL_CELL_EMPTY, xlrd.XL_CELL_BLANK):
                continue

            c = 0
            for j in range(QLIK_STAFFING_DATE_BEGIN):
                if j in QLIK_STAFFING_SKIPPED_COLUMNS:
                    continue
                worksheet.write(write_row_id, c, row_values[j])
                c += 1

            worksheet.write(write_row_id, QLIK_STAFFING_DATE_BEGIN - len(QLIK_STAFFING_SKIPPED_COLUMNS), row_values[i])
            worksheet.write(write_row_id, QLIK_STAFFING_DATE_BEGIN - len(QLIK_STAFFING_SKIPPED_COLUMNS) + 1, sheet.row_values(0)[i], date_format)
            write_row_id += 1
    workbook.close()
