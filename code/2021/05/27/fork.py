#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os


def main():
    print(f"Process ({os.getpid()}) start")

    pid = os.fork()
    if pid == 0:
        print(
            f"Child process ({os.getpid()}) start, parent process ({os.getppid()})"
        )
    else:
        print(f"Create a child process({pid})")


if __name__ == "__main__":
    main()
