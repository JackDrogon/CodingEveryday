#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'pp'

class CLI
  def initialize()
    
  end
end

class TinyVM

  attr_reader :regs

  def initialize()
    @regs = Array.new(6)
    @ip = 0
  end

  def process(opcodes)
    while @ip < opcodes.size
      opcode = opcodes[@ip]
      # pp opcode
      params = opcode[1..-1].map {|i| i.to_i}

      case opcode[0]
      when  /let/i
        @regs[params[0]] = params[1]
      when /add/i
        @regs[params[2]] = @regs[params[0]] + @regs[params[1]] 
      when /puti/i
        puts @regs[params[0]]
      when /gotol/i
        @ip = params[0]
        next
      when /xx/i
        r = opcode[1].to_i + opcode[2].to_i
      end

      @ip += 1
      # pp regs
    end
  end

end

tiny_vm = TinyVM.new
opcodes = []
while line = gets
  opcode = line.split
  opcodes << opcode
end

tiny_vm.process opcodes

# puts "---------- After Run ----------"
# pp tiny_vm.regs
