#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

class Point < Struct.new(:x, :y)
  def +(other_point)
    Point.new(x + other_point.x, y + other_point.y)
  end

  def inspect
    "#<Point (#{x}, #{y})>"
  end
end

class Point
  def -(other_point)
    Point.new(x - other_point.x, y - other_point.y)
  end
end
