#!/usr/bin/python
# coding: utf-8

import logging
import xlrd
from xlsxwriter.workbook import Workbook

class ExcelReader:
    def __init__(self, file_path):
        self.workbook = xlrd.open_workbook(file_path)
        self.sheet = None
        self.bind_sheet(0)

    def bind_sheet(self, index):
        self.sheet = self.workbook.sheet_by_index(index)
    
    def read_cell(self, row, col):
        return self.sheet.cell_value(row, col)

    def is_date(self, row, col):
        if self.sheet.cell_type(row, col) == xlrd.XL_CELL_DATE:
            return True
        return False

    def nrows(self):
        return self.sheet.nrows

    def ncols(self):
        return self.sheet.ncols
    
    # Not needed with this implementation, it's for future
    def close(self):
        pass

class ExcelWriter:
    def __init__(self, file_path):
        self.workbook = Workbook(file_path)
        self.cell_date_format = self.workbook.add_format({'num_format': 'dd/mm/yy'})
        self.sheets_list = []
        self.sheet = None
        self.max_row = -1

    def add_sheet(self, sheet_name):
        self.sheets_list.append(self.workbook.add_worksheet(sheet_name))

    def bind_sheet(self, index):
        if len(self.sheets_list) == 0:
            logging.error("No sheet in this excel file")
            return

        if index >= len(self.sheets_list):
            logging.error("Sheet index out of range")
            return

        self.sheet = self.sheets_list[index]

    def write_date_cell(self, row, col, value):
        if self.sheet == None:
            logging.error("No sheet selected")
            return

        self.sheet.write(row, col, value, self.cell_date_format)
        if row > self.max_row:
            self.max_row = row

    def write_cell(self, row, col, value):
        if self.sheet == None:
            logging.error("No sheet selected")
            return

        self.sheet.write(row, col, value)
        if row > self.max_row:
            self.max_row = row

    def concat(self, file_path, start_point=0, end_point=-1):
        reader = ExcelReader(file_path)
        if end_point == -1:
            end_point = reader.nrows()
        else:
            end_point += 1

        max_row = self.max_row
        for row in range(start_point, end_point):
            for col in range(0, reader.ncols()):
                if reader.is_date(row, col):
                    self.write_date_cell(
                        max_row + 1 + row - start_point, 
                        col,
                        reader.read_cell(row, col)
                    )
                else:
                    self.write_cell(
                        max_row + 1 + row - start_point, 
                        col,
                        reader.read_cell(row, col)
                    )
        reader.close()

    def close(self):
        self.workbook.close()

