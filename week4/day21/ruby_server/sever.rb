#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

#TODO Configure File
#TODO Concurrency

FILE_TYPE = {rb: 'ruby', php: 'php', html: 'cat'}

require 'socket'

port = ARGV[0] || 8080
server = TCPServer.new port

loop do
  client = server.accept

  # Parse Http Header
  first = client.gets
  puts first
  # GET / HTTP/1.1
  # ^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?
  if first =~ /(.*) (.*) HTTP/i
    puts $1, $2
    action = $1
    file = $2
  end

  while line = client.gets
    puts line
    break if line =~ /^\r/
  end


  if action.downcase == "get"
    file = $1 if file =~ /(.*)\?/
    file = '/index.html' if file == '/'
    suffix = $1 if file =~ /\.([^.]*)/
    file = File.expand_path(".#{file}")
    result = `#{FILE_TYPE[suffix.to_sym]} #{file}`
    puts result
    client.puts <<HEADER
HTTP/1.1 200 OK
Connection: close
Content-type: text/html

HEADER

  client.puts result
  end

  client.close

end
