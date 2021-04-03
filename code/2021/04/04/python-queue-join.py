#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue


def main():
    q = queue.Queue()
    for i in range(3):
        q.put(i)
    for i in range(3):
        print(q.get())
    q.join()


if __name__ == "__main__":
    main()
