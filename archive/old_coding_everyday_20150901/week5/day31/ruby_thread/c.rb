#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

t = Thread.new {
  for i in 1...2000000
    puts i
  end
}

t.join
