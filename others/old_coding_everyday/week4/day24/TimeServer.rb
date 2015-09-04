#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'gserver'

class TimeServer < GServer
  def initialize(port = 1234, *args)
    # super(port, *args)
    super
  end

  def serve(io)
    io.puts(Time.now)
  end
end

server = TimeServer.new
server.audit = true
server.start
server.join
