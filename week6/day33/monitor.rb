#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'monitor'

lock = Monitor.new
i = 0

threads = 10.times.map do
  Thread.new {
    lock.synchronize {
      1000.times {i += 1}
    }
  }
end

threads.each {|t| t.join}

puts i
