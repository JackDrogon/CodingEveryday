#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'open-uri'

open("https://www.ruby-lang.org") do |io|
  puts io.read
end
