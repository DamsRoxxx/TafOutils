#!/usr/bin/python
# coding: utf-8

import logging
from ArgsProcessing import *
from TED import ted
from TOS import tos
from HistoTED import histo_ted

# Call the appropriate function depending on the command line arguments
def call_appropriate_func(args):
    if args.ted:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        ted(args.input, args.output, args.start_date, args.end_date)
    elif args.tos:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        tos(args.input, args.output, args.start_date, args.end_date)
    elif args.hted:
        assert_args(args, {"input", "output", "start-date", "end-date", "parc"})
        histo_ted(args.input, args.output, args.start_date, args.end_date, args.parc)


if __name__ == '__main__':
    logging.basicConfig(
        # filename="TOSTEDCommand.log",
        format='%(levelname)s :: %(message)s',
        level=logging.DEBUG
    )
    args = parse_args()
    call_appropriate_func(args)
