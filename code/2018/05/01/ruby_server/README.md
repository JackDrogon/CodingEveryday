# <center> A Web Server With Ruby </center>

## V1
1. ### Parse Get/Post
2. ### Get Http Header
3. ### Send Message To Sever

```ruby
#!/usr/bin/env ruby
# -*- coding: utf-8 -*-

require 'socket'

port = ARGV[0] || 8080
server = TCPServer.new port

loop do
  client = server.accept

  first = client.gets
  puts first
  # GET / HTTP/1.1
  if first =~ /(GET|POST) (.*) HTTP/i
    puts $1, $2
  end

  while line = client.gets
    puts line
    break if line =~ /^\r/
  end

  #puts "End"

  client.puts 'HTTP/1.1 200 OK'
  client.puts 'Connection: close'
  client.puts 'Content-type: text/html'
  client.puts

  client.puts <<EOF
<!DOCTYPE html>
<html>
  <head>
    <title> Home </title>
    <body>
      <p> Hello,World! </p>
    <body>
  </head>
</html>
EOF

  client.close
end

```

## V2 Simple CGI

```ruby
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
```
FAQ:
1. FILE_TYPE创建Hash数组的时候 ruby等value忘记加上''了
2. 做File.expand_path 注意如果是类似'/index.html'的这种以'/'开头会直接认为是绝对路径
3. ``执行命令补全要加 #{}
