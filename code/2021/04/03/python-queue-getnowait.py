#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue


def main():
    q = queue.Queue()
    try:
        q.get_nowait()
    except queue.Empty:
        print('queue.Empty')


if __name__ == "__main__":
    main()
