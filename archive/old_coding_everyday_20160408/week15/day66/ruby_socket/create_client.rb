#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'socket'

client = Socket.new :INET, :STREAM

remote_addr = Socket.pack_sockaddr_in 80, "baidu.com"

client.connect remote_addr
