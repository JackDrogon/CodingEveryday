#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import multiprocessing
import os
import time
import random


def long_time_task(name):
    print(f'Run task {name} ({os.getpid()})...')

    start = time.time()
    sleep_time = random.random()
    time.sleep(sleep_time)
    print(f'Task {name} runs {time.time()-start} seconds.')

    return sleep_time


if __name__ == '__main__':
    print('Parent process %s.' % os.getpid())

    # create
    results = multiprocessing.Pool().map(long_time_task, range(5))
    print(results)
