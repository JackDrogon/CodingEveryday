#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'socket'

# Step1: create socket
server = Socket.new :INET, :STREAM
addr = Socket.pack_sockaddr_in 4481, '0.0.0.0'

# Step2: bind
server.bind(addr)

# Step3: listen
server.listen(5)

# Step4: loop, deal with client connection
loop do
  connection, _ = server.accept

  connection.write "Hello, World!\n"
  connection.close
end
