#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'pp'

class CLI

  def initialize()
    if ARGV[0]
      @opcodes = File.readlines(ARGV[0]).map { |line| line.strip.split(%r{[,\s]+}) }
    else
      while line = gets
        opcode = line.split
        @opcodes << opcode
      end
    end
    @opcodes.insert(0, nil)
    # pp @opcodes
  end

  def run()
    tiny_vm = TinyVM.new
    tiny_vm.process @opcodes
  end

end

class TinyVM

  attr_reader :regs

  def initialize()
    @regs = Array.new(6)
    @ip = 1
  end

  def process(opcodes)
    while @ip < opcodes.size
      opcode = opcodes[@ip]
      params = opcode[1..-1].map {|i| i.to_i}

      # pp opcode
      # pp regs

      case opcode[0]
      when  /let/i
        @regs[params[0]] = params[1]
      when /add/i
        @regs[params[2]] = @regs[params[0]] + @regs[params[1]] 
      when /and/i
        @regs[params[2]] = @regs[params[0]] && @regs[params[1]] 
      when /decr/i
        @regs[params[0]] -= 1
      when /div/i
        @regs[params[2]] = @regs[params[0]] / @regs[params[1]] 
      when /equal/i
        @regs[params[2]] = @regs[params[0]] == @regs[params[1]] 
      when /puti/i
        puts @regs[params[0]]
      when /goto/i
        @ip = params[0]
      when /gotor/i
        @ip = @regs[params[0]]
      when /gotol/i
        @ip = params[0]
        next
      when /nil/i
      end

      @ip += 1
    end
  end

end

cli = CLI.new
cli.run

# puts "---------- After Run ----------"
# pp tiny_vm.regs
