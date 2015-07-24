#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'stringio'

io = StringIO.new

io.puts("A")
io.puts("B")
io.puts("C")

io.rewind
p io.read

io.rewind
p io.gets
p io.gets
p io.gets
p io.gets
