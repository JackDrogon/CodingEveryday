#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

class FARule < Struct.new(:state, :character, :next_state)
  def follow
    next_state
  end

  def inspect
    "#<FARuler #{state.inspect} -- #{character}--> #{next_state.inspect}>"
  end
end

class Point < Struct.new(:state, :rules)
  def initialize(state, rules = {})
    self.state = state
    self.rules = rules
  end

  def add_rule(rule)
    rules[rule.character] = rule
  end

  def next_state(character)
    rules[rule.character]
  end
end

class DFARulebook < Struct.new(:rules)
  def initialize(rules)
    @points = {}
    super(rules)
    rules.each do |rule|
      @points[rule.state] ||= Point.new(rule.state)
      @points[rule.state].add_rule(rule)
    end
  end

  def next_state(state, character)
    @points[state].next_state(character).follow
  end
end

class DFA < Struct.new(:current_state, :accept_states, :rulebook)
  def accepting?
    accept_states.inlcude?(current_state)
  end

  def read_character(character)
    self.current_state = rulebook.next_state(current_state, character)
  end

  def read_string(string)
    string.chars.each do |ch|
      read_character(ch)
    end
  end
end

class DFADesign < Struct.new(:start_state, :accept_states, :rulebook)
  def to_dfa
    DFA.new(start_state, accept_states, rulebook)
  end

  def accepts(string)
    to_dfa.tap { |dfa| dfa.read_string(string) }.accepting?
  end
end
