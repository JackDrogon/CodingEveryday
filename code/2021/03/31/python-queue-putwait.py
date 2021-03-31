#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import queue


def main():
    try:
        q = queue.Queue(2)
        q.put('foo')
        q.put('bar')
        # 队列已满，继续在队列中插入字符串 '100'，等待5秒后会引发 queue.Full 异常
        q.put('hello', block=True, timeout=0.1)
    except queue.Full:
        print('queue.Full')


if __name__ == "__main__":
    main()
