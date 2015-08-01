#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'socket'
require 'nio'

class ChatServer
  def initialize(host, port)
    @selector = NIO::Selector.new

    puts "Listening on #{host}:#{port}"
    @server = TCPServer.new(host, port)

    @connected_clients = {}

    monitor = @selector.register(@server, :r)
    monitor.value = proc { accept }
  end

  def accept
    socket = @server.accept
    _, port, host = socket.peeraddr
    puts "*** #{host}:#{port} connected"

    monitor = @selector.register(socket, :rw)
    monitor.value = {call: proc {ask_username}, socket: socket, read_buf: String.new, write_buf: String.new}
  end

  def ask_username(monitor)
    socket = monitor.value[:socket]
    read_buf = monitor.value[:buf]
    if monitor.readable?
      read_buf << socket.read_nonblock(4096)
      if read_buf.find '\n'
      end
    end
  end

  def unbind()
  end

  def join
  end

  def run
    while true
      @selector.select {|monitor| monitor.value[:call].call monitor}
    end
  end
end
