#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue


def main():
    try:
        q = queue.Queue(2)
        q.put('foo')
        q.put('bar')
        q.put_nowait('hello')
    except queue.Full:
        print('queue.Full')


if __name__ == "__main__":
    main()
