#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

string = <<-EOS
  The body of the string is the input lines up to
    one starting with the same text that followed the '<<'
  EOS

puts string.gsub(/^.{#{(string.slice(/^ +/) || '').length}}/, '')
