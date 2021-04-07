#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from queue import Queue
import random
import threading
import time


class Producer(threading.Thread):
    def __init__(self, t_name, queue):
        threading.Thread.__init__(self, name=t_name)
        self.data = queue

    def run(self):
        for i in range(5):
            print("%s: %s is producing %d to the queue!" %
                  (time.ctime(), self.getName(), i))
            self.data.put(i)  # 将生产的数据放入队列
            time.sleep(random.randrange(10) / 5)
        print("%s: %s finished!" % (time.ctime(), self.getName()))


class Consumer(threading.Thread):
    def __init__(self, t_name, queue):
        threading.Thread.__init__(self, name=t_name)
        self.data = queue

    def run(self):
        for i in range(5):
            val = self.data.get()  # 拿出已经生产好的数据
            print("%s: %s is consuming. %d in the queue is consumed!" %
                  (time.ctime(), self.getName(), val))
            time.sleep(random.randrange(5))
            self.data.task_done()  # 告诉队列有关这个数据的任务已经处理完成
        print("%s: %s finished!" % (time.ctime(), self.getName()))


def main():
    queue = Queue()

    producer = Producer('Producer', queue)
    consumer = Consumer('Consumer', queue)
    producer.start()
    consumer.start()

    producer.join()
    consumer.join()
    queue.join()  # 阻塞，直到生产者生产的数据全都被消费掉

    print('All threads terminate!')


if __name__ == '__main__':
    main()
