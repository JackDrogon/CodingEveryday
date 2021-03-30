#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue
import pprint


def main():
    q = queue.PriorityQueue()
    data1 = (1, 'oh')
    data2 = (3, 'python')
    data3 = (2, 'foo')
    style = (data2, data3, data1)

    for i in style:
        q.put(i)
    pprint.pprint(q.queue)

    for i in range(3):
        print(q.get())
    pprint.pprint(q.queue)


if __name__ == "__main__":
    main()
