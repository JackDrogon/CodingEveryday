#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'redis'

r = Redis.new

# Exists
p r.exists('redis-db')                      # => false

# Set && Get
p r.set('redis-db', "Hello")                # => "OK"
p r.get('redis-db')                         # => "Hello"

# Append
p r.append('redis-db', ' World')            # => 11

# Strlen
p r.strlen('redis-db')                      # => 5

# MGet && MSet
p r.mset('hello', 'world', 'foo', 'bar')    # => "OK"
p r.mget('hello', 'foo')                    # => ['world', 'bar']

# Incr && Decr
p r.incr('num')                             # => 1
p r.incrby('num', 10)                       # => 11
p r.decr('num')                             # => 10
p r.decrby('num', 11)                       # => -1
p r.getset('num', 0)                        # => '-1'
p r.get('num')                              # => '0'

# Flush && Delete db
p r.flushdb


# BITCOUNT BITOP BITPOS GETBIT GETRANGE GETSET INCRBYFLOAT MSETNX PSETEX SETBIT SETEX SETNX SETRANGE
