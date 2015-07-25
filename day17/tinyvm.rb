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
      when /getc/i
        @regs[params[0]] = STDIN.getc
      when /geti/i
        @regs[params[0]] = STDIN.gets.chomp!.to_i
      when /goto/i
        @ip = params[0]
        next
      when /gotor/i
        @ip = @regs[params[0]]
        next
      when /gotol/i
        @ip = params[0]
        next
      when /gt/i
        @regs[params[2]] = @regs[params[0]] < @regs[params[1]] 
      when /if/i
        if @regs[params[0]]
          @ip = @ip + 1
        else
          @ip = @ip + 2
        end
        next
      when /incr/i
        @regs[params[0]] += 1
      when /lsft/i
        @regs[params[0]] <<= 1
      when /lt/i
        @regs[params[2]] = @regs[params[0]] < @regs[params[1]] 
      when /mcpy/i
        @regs[params[1]] = @regs[params[0]]
      when /mod/i
        @regs[params[2]] = @regs[params[0]] % @regs[params[1]] 
      when /mul/i
        @regs[params[2]] = @regs[params[0]] * @regs[params[1]] 
      when /noop/i
      when /not/i
        @regs[params[0]] = !@regs[params[0]]
      when /or/i
        @regs[params[2]] = @regs[params[0]] || @regs[params[1]] 
      when /putc/i
        puts @regs[params[0]]
      when /puti/i
        puts @regs[params[0]]
      when /sub/i
        @regs[params[2]] = @regs[params[0]] - @regs[params[1]] 
      when /swap/i
        @regs[params[1]], @regs[params[0]] = @regs[params[0]], @regs[params[1]] 
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
