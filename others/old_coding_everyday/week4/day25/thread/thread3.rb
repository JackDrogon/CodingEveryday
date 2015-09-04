#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

def fun
  puts "Begin Fun at: #{Time.now} in thread: #{Thread.current}"
  0.upto(10000000) { |i|
  }
  puts "End Fun at: #{Time.now} in thread: #{Thread.current}"
end

T1 = Thread.new{fun()}
T1.join
puts "Main at: #{Time.now} in thread: #{Thread.current}"
