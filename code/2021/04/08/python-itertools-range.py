#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools


def main():
    # count, cycle, repeat
    r = itertools.count(1, 2)
    for i in range(3):
        print(next(r))

    r = itertools.cycle("ABC")
    for i in range(4):
        print(next(r))


if __name__ == "__main__":
    main()
