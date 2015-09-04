#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'treetop'
Treetop.load 'list'

parser = ListParser.new
puts parser.parse('[hello]')
