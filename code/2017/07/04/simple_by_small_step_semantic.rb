#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

# TODO: 符号嵌套的表示, 主要是添加括号
# TODO: Add function support, which local/global scope, which not limit params(can be realized as hash, variable name as key)
# TODO: scope support

# FIXME: 这个无法使用不存在statement

# DONE                : ------------------
# Sutructure          : Number, Boolean
# Assign              : Assign
# Arithmetic Operator : Add, Subtract, Multiply, Divide
# Binary Operator     : LessThan, Equal
# Construct           : If, Unless; While, Until, DoWhile, For

class Number < Struct.new(:value)
  def reducible?
    false
  end

  def to_s
    value.to_s
  end

  def inspect
    "<<#{self}>>"
  end
end

class Add < Struct.new(:left, :right)
  def reducible?
    true
  end

  def reduce(environment)
    if left.reducible?
      Add.new(left.reduce(environment), right)
    elsif right.reducible?
      Add.new(left, right.reduce(environment))
    else
      Number.new(left.value + right.value)
    end
  end

  def to_s
    "#{left} + #{right}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Subtract < Struct.new(:left, :right)
  def reducible?
    true
  end

  def reduce(environment)
    if left.reducible?
      Subtract.new(left.reduce(environment), right)
    elsif right.reducible?
      Subtract.new(left, right.reduce(environment))
    else
      Number.new(left.value - right.value)
    end
  end

  def to_s
    "#{left} - #{right}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Multiply < Struct.new(:left, :right)
  def reducible?
    true
  end

  def reduce(environment)
    if left.reducible?
      Multiply.new(left.reduce(environment), right)
    elsif right.reducible?
      Multiply.new(left, right.reduce(environment))
    else
      Number.new(left.value * right.value)
    end
  end

  def to_s
    "#{left} * #{right}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Divide < Struct.new(:left, :right)
  def reducible?
    true
  end

  def reduce(environment)
    if left.reducible?
      Divide.new(left.reduce(environment), right)
    elsif right.reducible?
      Divide.new(left, right.reduce(environment))
    else
      Number.new(left.value / right.value)
    end
  end

  def to_s
    "#{left} / #{right}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Boolean < Struct.new(:value)
  def reducible?
    false
  end

  def to_s
    value.to_s
  end

  def inspect
    "<<#{self}>>"
  end
end

class LessThan < Struct.new(:left, :right)
  def reducible?
    true
  end

  def reduce(environment)
    if left.reducible?
      LessThan.new(left.reduce(environment), right)
    elsif right.reducible?
      LessThan.new(left, right.reduce(environment))
    else
      Boolean.new(left.value < right.value)
    end
  end

  def to_s
    "#{left} < #{right}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Equal < Struct.new(:left, :right)
  def reducible?
    true
  end

  def reduce(environment)
    if left.reducible?
      Equal.new(left.reduce(environment), right)
    elsif right.reducible?
      Equal.new(left, right.reduce(environment))
    else
      Boolean.new(left.value == right.value)
    end
  end

  def to_s
    "#{left} < #{right}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Variable < Struct.new(:name)
  def reducible?
    true
  end

  def reduce(environment)
    environment[name]
  end

  def to_s
    name.to_s
  end

  def inspect
    "<<#{self}>>"
  end
end

class DoNothing
  def ==(other_statement)
    other_statement.instance_of?(DoNothing)
  end

  def reducible?
    false
  end

  def to_s
    'do-nothing'
  end

  def inspect
    "<<#{self}>>"
  end
end

class Assign < Struct.new(:name, :expression)
  def reducible?
    true
  end

  def reduce(environment)
    if expression.reducible?
      [Assign.new(name, expression.reduce(environment)), environment]
    else
      [DoNothing.new, environment.merge({ name => expression })]
    end
  end

  def to_s
    "#{name} = #{expression}"
  end

  def inspect
    "<<#{self}>>"
  end
end

class Sequence < Struct.new(:first, :second)
  def reducible?
    true
  end

  def reduce(environment)
    case first
    when DoNothing.new
      [second, environment]
    else
      reduce_first, reduce_environment = first.reduce(environment)
      [Sequence.new(reduce_first, second), reduce_environment]
    end
  end

  def to_s
    "#{first}; #{second}"
  end

  def inspect
    "«#{self}»"
  end
end

class If < Struct.new(:condition, :consequence, :alternative)
  def reducible?
    true
  end

  def reduce(environment)
    if condition.reducible?
      [If.new(condition.reduce(environment), consequence, alternative), environment]
    else
      case condition
      when Boolean.new(true)
        [consequence, environment]
      when Boolean.new(false)
        [alternative, environment]
      end
    end
  end

  def to_s
    "if (#{condition}) { #{consequence} } else { #{alternative} }"
  end

  def inspect
    "«#{self}»"
  end
end

class UnLess < Struct.new(:condition, :consequence, :alternative)
  def reducible?
    true
  end

  def reduce(environment)
    if condition.reducible?
      [UnLess.new(condition.reduce(environment), consequence, alternative), environment]
    else
      case condition
      when Boolean.new(false)
        [consequence, environment]
      when Boolean.new(true)
        [alternative, environment]
      end
    end
  end

  def to_s
    "unless (#{condition}) { #{consequence} } else { #{alternative} }"
  end

  def inspect
    "«#{self}»"
  end
end

class While < Struct.new(:condition, :body)
  def reducible?
    true
  end

  def reduce(environment)
    [If.new(condition, Sequence.new(body, self), DoNothing.new), environment]
  end

  def to_s
    "while (#{condition}) { #{body} }"
  end

  def inspect
    "«#{self}»"
  end
end

class DoWhile < Struct.new(:condition, :body)
  def reducible?
    true
  end

  def reduce(environment)
    [If.new(condition, Sequence.new(body, self), DoNothing.new), environment]
    [Sequence(body, While.new(condition, body)), environment]
  end

  def to_s
    "do { #{body} } while (#{condition});"
  end

  def inspect
    "«#{self}»"
  end
end

class Until < Struct.new(:condition, :body)
  def reducible?
    true
  end

  def reduce(environment)
    [Unless.new(condition, Sequence.new(body, self), DoNothing.new), environment]
  end

  def to_s
    "until (#{condition}) { #{body} }"
  end

  def inspect
    "«#{self}»"
  end
end

class For < Struct.new(:defination, :condition, :operation, :body)
  def reducible?
    true
  end

  def reduce(environment)
    # [Sequence(defination, If.new(condition, Sequence.new(Sequence(operation, body), self)), DoNothing.new), environment]
    [Sequence(defination, Sequence(While.new(condition, body), operation)), environment]
  end

  def to_s
    "for (#{defination}; #{condition}; #{operation}) { #{body} }"
  end

  def inspect
    "«#{self}»"
  end
end

class Function
end

class Machine < Struct.new(:statement, :environment)
  def step
    self.statement, self.environment = statement.reduce(environment)
  end

  def run
    while statement.reducible?
      puts "#{statement}, #{environment}"
      step
    end
    puts "#{statement}, #{environment}"
  end
end

if $0 == __FILE__
  Machine.new( While.new( LessThan.new(Variable.new(:x), Number.new(5)), Assign.new(:x, Multiply.new(Variable.new(:x), Number.new(3))) ), { x: Number.new(1) } ).run
end
