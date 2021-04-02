#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue


def main():
    q = queue.Queue()
    try:
        q.get(block=True, timeout=0.1)
    except queue.Empty:
        print('queue.Empty')


if __name__ == "__main__":
    main()
