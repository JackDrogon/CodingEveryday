#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# NOTE: 打印匹配的pattern的行和它之前的history_num行

from collections import deque


def search(lines, pattern, history_num=5):
    prevlines = deque(maxlen=history_num)
    for line in lines:
        if pattern in line:
            yield line, prevlines
        prevlines.append(line)


def main():
    with open(__file__) as f:
        for line, prevlines in search(f, 'line', 5):
            for pline in prevlines:
                print(pline, end='')
            print(line, end='')
            print('-' * 20)


if __name__ == "__main__":
    main()
