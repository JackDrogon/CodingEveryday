#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from multiprocessing import Process
import os


def hello(name):
    print(
        "hello", name,
        f"in child process ({os.getpid()}), parent process ({os.getppid()})")


def main():
    print(f"main process({os.getpid()})")

    process = Process(target=hello, args=('world', ))
    process.start()
    process.join()


if __name__ == "__main__":
    main()
