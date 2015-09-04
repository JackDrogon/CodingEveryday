#!/usr/bin/env ruby

require 'socket'
require 'nio'

class EchoServer
  def initialize(host, port)
    @selector = NIO::Selector.new

    puts "Listening on #{host}:#{port}"
    @server = TCPServer.new(host, port)

    monitor = @selector.register(@server, :r)
    monitor.value = proc { accept }
  end

  def run
    while true
      @selector.select { |monitor| monitor.value.call monitor }
    end
  end

  def accept
    socket = @server.accept
    _, port, host = socket.peeraddr
    puts "*** #{host}:#{port} connected"
    time socket
  end

  def time(socket)
    socket.write_nonblock("#{Time.now}\r\n")
  rescue EOFError
    _, port, host = socket.peeraddr
    puts "*** #{host}:#{port} disconnected"
  rescue Errno::ECONNRESET
    puts "*** #{host}:#{port} reset"
  ensure
    socket.close
  end
end

if $0 == __FILE__
  Signal.trap("PIPE") do
    puts "------ Haha SIGPIPE ------"
  end
  # EchoServer.new("127.0.0.1", 1234).run
  # EchoServer.new("0.0.0.0", 1234).run
  EchoServer.new("localhost", 1234).run
end
