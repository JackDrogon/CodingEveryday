#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'socket'

# Add threadpool / fiber
# Add logger
# Add invalid path

class WebServerCLI
  def initialize(port = 1055)
    @port = port
    @server = WebServer.new port
  end

  def run_server()
    @server.run
  end
end

class WebServer
  def initialize(port)
    @server = TCPServer.new port
  end

  def run
    loop do
      client = @server.accept
      Thread.new {
        deal_with_client(client)
      }
    end
  end

  def deal_with_client(client)
    method_line = client.gets
    # 此处可以参考rack的request -> param
    if method_line =~ /(.*) (.*) HTTP\/(.*)/i
      method = $1.upcase
      path = $2
      http_version = $3
    else
      client.send HTTP::UNIMPLEMENTED
      client.close
    end

    puts "Method: #{method}, Path: #{path}, HTTPVerison: #{http_version}"
    if ["GET", "POST"].include? method
      if method == "GET"
        result = HTTP::get path
        client.print result
        client.close
      end
      HTTP::post 'path' if method == "POST"
    else
      client.print HTTP::UNIMPLEMENTED
      client.close
    end

  end
end

class HTTP
  HEADER = <<HEADER
HTTP/1.0 200 OK\r
Server: little_httpd/0.1.0\r
Content-Type: text/html\r
\r
HEADER

  NOT_FOUND = <<NOT_FOUND
HTTP/1.0 404 NOT FOUND\r
Server: little_httpd/0.1.0\r
Content-Type: text/html\r
\r
<HTML><TITLE>Not Found</TITLE>\r
<BODY><P>The server could not fulfill\r
your request because the resource specified\r
is unavailable or nonexistent.\r
</BODY></HTML>\r
NOT_FOUND

  BAD_REQUEST = <<BAD_REQUEST
HTTP/1.0 400 BAD REQUEST\r
Server: little_httpd/0.1.0\r
Content-Type: text/html\r
\r
<P>Your browser sent a bad request, such as a POST without a Content-Length.\r
BAD_REQUEST

  UNIMPLEMENTED = <<UNIMPLEMENTED
HTTP/1.0 501 Method Not Implemented\r
Server: little_httpd/0.1.0\r
Content-Type: text/html\r
\r
<HTML><HEAD><TITLE>Method Not Implemented\r
</TITLE></HEAD>\r
<BODY><P>HTTP request method not supported.\r
</BODY></HTML>\r
UNIMPLEMENTED

  CANNOT_EXECUTE = <<CANNOT_EXECUTE
HTTP/1.0 500 Internal Server Error\r
Content-type: text/html\r
\r
P>Error prohibited CGI execution.\r
CANNOT_EXECUTE

  def error()
  end

  def self.get(path)
    path = "./hotdoc" + path
    path << 'index.html' if path.end_with? '/'
    if File.expand_path(path).start_with?(File.expand_path '.')
      puts "Real Path: #{path}"
      begin
        stat = File::stat path
        get_file path
      rescue Exception => e
        puts e.message
        puts e.backtrace.inspect
      end
    else
      NOT_FOUND
    end
  end

  def self.get_file(path)
    File.read path
  end

  def self.post()
  end

  def self.execute_cgi(method, path, query_string, content)
    begin
      ENV["REQUEST_METHOD"] = method
      ENV["QUERY_STRING"] = query_string
      ENV["CONTENT_LENGTH"] =
      `echo ${content} | #{path}`
    rescue
      CANNOT_EXECUTE
    end
  end
end

WebServerCLI.new.run_server
