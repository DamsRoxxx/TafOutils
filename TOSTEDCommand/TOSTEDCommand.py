#!/usr/bin/python
# coding: utf-8

import logging
from ArgsProcessing import *
from TED import ted
from TOS import tos
from HistoTED import histo_ted
from FilterEquipments import filter_equipments
from RemoveDuplicates import remove_duplicates
from Compare import compare
from ExtractDriverNDSI import extract_driver_ndsi
from AudaceTED import audace_ted
from AudaceTOS import audace_tos
from Merge import merge_files

# Call the appropriate function depending on the command line arguments
def call_appropriate_func(args):
    assert_only_one_arg(args, {"ted", "tos", "hted", "filter", "remove-duplicates", "compare"})

    #/!\ Dirty
    # When the list of input contain only one arg, pass only this arg
    if len(args.input) == 1:
        args.input = args.input[0]

    if args.ted:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        ted(args.input, args.output, args.start_date, args.end_date)
    elif args.tos:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        tos(args.input, args.output, args.start_date, args.end_date)
    elif args.hted:
        assert_args(args, {"input", "output", "start-date", "end-date", "parc"})
        histo_ted(args.input, args.output, args.start_date, args.end_date,
                  args.parc)
    elif args.extract_driver_ndsi:
        assert_args(args, {"input", "output"})
        extract_driver_ndsi(args.input, args.output)
    elif args.filter:
        assert_args(args, {"input", "output"})
        filter_equipments(args.input, args.output, args.filter)
    elif args.remove_duplicates:
        assert_args(args, {"input", "output"})
        remove_duplicates(args.input, args.output)
    elif args.compare:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        compare(args.input, args.output, args.start_date, args.end_date)
    elif args.ated:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        audace_ted(args.input, args.output, args.start_date, args.end_date)
    elif args.atos:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        audace_tos(args.input, args.output, args.start_date, args.end_date)
    elif args.merge_histo_ted:
        assert_args(args, {"input", "output"})
        merge_files(args.output, args.input)


if __name__ == '__main__':
    logging.basicConfig(
        # filename="TOSTEDCommand.log",
        format='%(levelname)s :: %(message)s',
        level=logging.DEBUG
    )
    args = parse_args()
    call_appropriate_func(args)
