#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess


def main():
    cmd = ['nslookup', 'www.python.org']
    print("$ " + " ".join(cmd))
    exit_code = subprocess.call(cmd)
    print(f'Exit code {exit_code}')


if __name__ == "__main__":
    main()
