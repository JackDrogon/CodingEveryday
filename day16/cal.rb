#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'date'

d = Date.today
d = d - d.day + 1

puts "      #{d.month}  #{d.year}    "
puts "日 一 二 三 四 五 六"
print "   " * (d.wday % 7) + " " + d.day.to_s

pd = d+1
while pd.month == d.month
  printf "%2d ", pd.day
  puts if pd.wday == 6
  pd += 1
end
