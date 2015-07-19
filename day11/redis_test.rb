#!/usr/bin/env ruby
# coding: utf-8

require "redis"
require "pp"

redis = Redis.new

# get set incr
redis.set "foo", "foo"
puts redis.get "foo"            # => foo
redis.append "foo", "bar"
puts redis.get "foo"            # => foobar

redis.set "hello", 1
puts redis.get "hello"
pp redis.get "hello"
redis.incr "hello"
puts redis.get "hello"
redis.decr "hello"
puts redis.get "hello"

redis.hset "myhash", "field1", "foo"
puts redis.hget "myhash", "field1"
