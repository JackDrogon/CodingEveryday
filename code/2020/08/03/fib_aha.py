#!/usr/bin/env python3
# encoding: utf-8


def fib(n):
    assert (n >= 0)

    if n < 2:
        return n

    return fib(n - 1) + fib(n - 2)


def main():
    print(f"Fibonacci 30 is {fib(30)}")


if __name__ == "__main__": main()
