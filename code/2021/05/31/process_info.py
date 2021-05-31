#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from multiprocessing import Process
import os


def info(title):
    print(title)
    # NOTE: child __mp_main__
    print('module name:', __name__)
    print('parent process:', os.getppid())
    print('process id:', os.getpid())


def f(name):
    info('function f')
    print('hello', name)


def main():
    info('main line')
    p = Process(target=f, args=('bob', ))
    p.start()
    p.join()


if __name__ == "__main__":
    main()
