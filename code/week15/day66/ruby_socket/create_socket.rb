#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'socket'
# socket = Socket.new Socket::AF_INET, Socket::SOCK_STREAM
# socket = Socket.new :INET, :STREAM
socket = Socket.new :INET6, :STREAM
