#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def main():
    from timeit import timeit
    print(timeit("factorial(999)", "from math import factorial", number=10))


if __name__ == "__main__":
    main()
