#!/usr/bin/python
# coding: utf-8

import logging
from ArgsProcessing import *
from TED import *
from TOS import *

# Call the appropriate function depending on the command line arguments
def call_appropriate_func(args):
    if args.extract_ted_logs:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        extract_ted_logs(args.input, args.output, args.start_date, args.end_date)
    elif args.extract_tos_logs:
        assert_args(args, {"input", "output", "start-date", "end-date"})
        extract_tos_logs(args.input, args.output, args.start_date, args.end_date)

if __name__ == '__main__':
    logging.basicConfig(
        # filename="TOSTEDCommand.log",
        format='%(levelname)s :: %(message)s',
        level=logging.DEBUG
    )
    args = parse_args()
    call_appropriate_func(args)
