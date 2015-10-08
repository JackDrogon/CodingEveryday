#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

# 写一个triangle(a,b,c)函数，判断是等边，等腰，或一般三角形，并且能在有一边小于等于零或两边之和小于第三边的情况下raise一个error

def triangle(a, b, c)
  raise TriangleError if [a,b,c].min <= 0
  x, y, z = [a,b,c].sort
  raise TriangleError if x + y <= z
  [:equilateral,:isosceles,:scalene].fetch([a,b,c].uniq.size - 1)
end
