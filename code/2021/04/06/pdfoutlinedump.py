#!/usr/bin/env python3
# encoding: utf-8
"""
pdfoutlinedump.py

"""

from optparse import OptionParser
from PyPDF2 import PdfFileReader


def flattenWithLevel(iterable, level=0):
    for element in iter(iterable):
        if isinstance(element, list):
            for e in flattenWithLevel(element, level + 1):
                yield e
        else:
            yield {"level": level, "content": element}


def main():
    parser = OptionParser()
    parser.add_option("-t", "--tabulator", dest="tab", default="\t")
    (options, args) = parser.parse_args()

    for fileName in args:
        pdf = PdfFileReader(open(fileName, "rb"))
        for outline in flattenWithLevel(pdf.getOutlines()):
            print(options.tab * int(outline["level"]),
                  outline["content"]["/Title"])


if __name__ == "__main__":
    main()
