#!/usr/bin/env python
# encoding: utf-8

# References
# http://www.ityouknow.com/python/2019/10/12/python-random-031.html
# https://www.cnblogs.com/liangmingshen/p/8909376.html
# https://docs.python.org/zh-cn/3/library/random.html

import random


def main():
    # random()函数可以随机生成一个[0,1)的浮点数
    print(random.random())

    # randint(a,b) 随机正式n a <= n <= b
    print(random.randint(5, 50))

    # uniform(a,b) 随机浮点数f min(a,b) <= f <= max(a,b),
    print(random.uniform(2, 5))
    print(random.uniform(5, 2))

    # randrange([start], stop[, step])
    print(random.randrange(1, 10))
    # error print(random.randrange(10,1))
    # 先从1到10的产生一个间隔是2的等差数列，再从中随机获取一个随机数。
    print(random.randrange(1, 10, 2))

    # choice(seq) 非空序列 sequence 中随机返回一个数
    strlist = ['C++', 'C#', 'Java', 'Python']
    strtemp = ('Do you love python')
    print(random.choice(strlist))
    print(random.choice(strtemp))

    # shuffle(x[, random]) 将列表中的元素打乱
    lst = ['A', 'B', 'C', 'D', 'E']
    random.shuffle(lst)
    print(lst)

    # sample(sequence, k)
    # 函数可以获取从总体序列或集合中选择的唯一元素的k长度列表
    # sample()函数不会修改原有序列
    # 它主要用在无重复的随机抽样场景，实现从大量样本中快速进行抽样
    lst = [1, 2, 3, 4, 5]
    print(random.sample(lst, 4))
    print(lst)


if __name__ == "__main__":
    main()
