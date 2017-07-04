#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'timeout'

begin
  status = Timeout::timeout(5) {
    puts Time.now
    i = 0
    loop do
      ++i
    end
  }
end

puts Time.now
puts status
sleep(10)
puts Time.now
