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
    pool = multiprocessing.Pool()
    results = []
    # dispatch
    for i in range(5):
        result = pool.apply_async(long_time_task, args=(i, ))
        results.append(result)
    print('Waiting for all subprocesses done...')

    # close
    pool.close()

    # join
    pool.join()
    print('All subprocesses done.')

    results = [result.get() for result in results]
    print(results)
