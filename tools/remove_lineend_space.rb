#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

src, dst = ARGV
exit 1 if !src && !dst

File.write dst, File.readlines(src) .map{ |line| line.rstrip << "\n" } .reduce(:+)
