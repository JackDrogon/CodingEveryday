#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

# TODO: ListLexer realize a generate -> each ... for.. etc
# TODO: 添加容错部分

class ListLexer

  EOF_TYPE = "EOF"
  LETTERS = ("a".."z").to_a + ("A".."Z").to_a

  def initialize(input)
    @text = @input
    @input = input
  end

  def next_token()
    while @input
      case @input
      when ""
        @input = nil
      when /^\s+/
        @input = $'
      when /^(\w)+/
        @input = $'
        return Token.new $1, "NAME"
      when /^\[/
        @input = @input[1..-1]
        return Token.new '[', "LBRACK"
      when /^\]/
        @input = @input[1..-1]
        return Token.new ']', "RBRACK"
      when /^,/
        @input = @input[1..-1]
        return Token.new ',', "COMMA"
      else
        return Token.new @input, "LEXER_ERROR"
      end
    end
    Token.new "EOF", EOF_TYPE
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
