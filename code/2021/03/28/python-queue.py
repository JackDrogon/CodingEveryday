#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue
import pprint


pp = pprint.PrettyPrinter(indent=4)


def main():
    q = queue.Queue()
    for i in range(9):
        q.put(i)
    pp.pprint(q.queue)

    for i in range(9):
        print(q.get())
    pp.pprint(q.queue)


if __name__ == "__main__":
    main()
