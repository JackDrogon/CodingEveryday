#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'socket'

servers = Socket.tcp_server_sockets(4481)

p servers
