#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

file = __FILE__
File.open(file).each_line do |line|
  p line
end

STDIN.each_line do |line|
  p line
end
