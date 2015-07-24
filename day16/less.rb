#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

unless ARGV[0]
  puts "Need a file name."
else
  lines = File.open(ARGV[0]).readlines
  index = 0
  loop do
    break if (index >= lines.size)

    lines[index..index+10].each { |line| print line }
    STDOUT.print ": "

    quit = false
    loop do
      answer = STDIN.gets.chomp!
      if "yY".include? answer
        index += 10
        break
      elsif "nN".include? answer
        quit = true
        break
      else
        STDIN.print "You shoud input (nNyY): "
      end
    end

    break if quit
  end
end
