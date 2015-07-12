#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

# @doc ruby_version >= 1.9

l = -> {puts "Hello, Lambda!"}
l.call

p = Proc.new {|x| puts x}
p.call("Hello, Proc!")
