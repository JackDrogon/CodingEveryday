#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from multiprocessing import Process, Queue
import os
import time
import random


def write(q):
    print(f'Process to write: {os.getpid()}')
    for value in ['A', 'B', 'C']:
        print(f'Put {value} to queue')
        q.put(value)
        time.sleep(random.random())


def read(q):
    print(f'Process to read: {os.getpid()}')
    while True:
        value = q.get(True)
        print(f'Get {value} from queue')


def main():
    q = Queue()
    writer_process = Process(target=write, args=(q, ))
    reader_process = Process(target=read, args=(q, ))

    writer_process.start()
    reader_process.start()
    writer_process.join()

    # FIXME(Drogon): wait to get all value
    time.sleep(1)
    reader_process.terminate()


if __name__ == "__main__":
    main()
