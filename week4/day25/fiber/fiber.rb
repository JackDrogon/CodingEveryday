#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'fiber'

## resume的返回值来自于对应的yeild，此处应该与ruby block的yeild是一致的
## yeild的返回值来自于下一次的resume


## TODO: 为什么会有默认的fiber，在main的namespace中，会有fiber

f = Fiber.new {
  puts "Fiber echo hello"  
  puts Fiber.current
  acc = Fiber.yield("From Fiber f")
  puts Fiber.current
  puts "Accept From outside => #{acc}"
  puts "Fiber echo world"
  "Fiber End"
}

puts "Hello"
puts f.resume
puts Fiber.current
puts "World"
puts f.resume("Haha")
puts Fiber.current
