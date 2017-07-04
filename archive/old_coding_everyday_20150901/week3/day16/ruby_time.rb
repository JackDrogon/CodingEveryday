#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

p Time.now

# year 年
# month 月
# day 日
# hour 时
# min 分
# sec 秒
# usec 毫秒
# to_i 1970年1月1日到现在的秒数 unix时间戳
# wday 一周第几天
# mday 一个月第几天
# yday 一年第几天 1->1月1日
# zone 时区(CST等)


t = Time.new
p t.year, t.month, t.day
p t.yday
p t.zone


# ==============================
# Date处理不包含时间的日期, 是以天为单位
require 'date'
d = Date.today
puts d
