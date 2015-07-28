#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'date'

d = Date.today
d = d - d.day + 1

# 判断第几周 (mday - mday1 + wday1 - 1) / 7
# 如果是判断是第几周是从星期日开始的话，直接(mday - mday1 + wday1) / 7

# 此处考虑一个月的第一天可能是星期日 显示是从星期日开始的 
# 这样就判断beg就行了 如果cal[0][6] =nil beg = 1否则是0, beg -> cal的第一层下标

# cal =  Array.new(5, Array.new(7)) -> 这样写有问题是共享的指针，一个第二层array改了所有都改了
cal = 5.times.map {Array.new(7)}
pd = d
while pd.month == d.month
  wek = (pd.mday - d.mday + d.wday) / 7
  cal[wek][pd.wday] = pd.mday
  pd += 1
end

p cal
