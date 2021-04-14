#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def highorder_func(n):
    return lambda x: x + n


def main():
    sum = lambda a, b, c: a + b + c
    print(sum(1, 2, 3))
    incr = highorder_func(10)
    print(incr(1))


if __name__ == "__main__":
    main()
