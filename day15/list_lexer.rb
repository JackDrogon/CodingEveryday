#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

# TODO: ListLexer realize a generate -> each ... for.. etc
# TODO: 添加容错部分

class ListLexer

  EOF_TYPE = "EOF"
  LETTERS = ("a".."z").to_a + ("A".."Z").to_a

  def initialize(input)
    @input = input
    @index = 0
    @c = @input[@index]
  end

  def next_token()
    while @c
      ws()
      case @c
      when "["
        consume()
        return Token.new '[', "LBRACK"
      when "]"
        consume()
        return Token.new ']', "RBRACK"
      when ","
        consume()
        return Token.new ',', "COMMA"
      else
        return Token.new name(), "NAME"
      end
    end
    Token.new "EOF", EOF_TYPE
  end

  def name()
    buf = ''
    while LETTERS.include? @c
      buf << @c
      consume()
    end
    buf
  end

  def ws()
    " \t\r\n".include? @c
  end

  def ws()
    while " \t\r\n".include? @c
      consume()
    end
  end

  def consume()
    @index += 1
    if (@index >= @input.length())
      @c = nil
    else
      @c = @input[@index]
    end
  end

end

class Token
  attr_reader :type
  def initialize(text, type)
    @text = text
    @type = type
  end

  def to_s
    "<'#{@text}', #{@type}>"
  end
end

list_lexer = ListLexer.new(ARGV[0])
t = list_lexer.next_token
while t.type != ListLexer::EOF_TYPE
  puts t
  t = list_lexer.next_token
end
puts t # EOF
