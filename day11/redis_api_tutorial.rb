#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'redis'

r = Redis.new

# Keys
r.set("redis_db", "great k / v storage")             # => OK
r.get("redis_db")                                    # => "great k / v storage"

# Counters
r.incr("redis_db")                                   # => 1
r.decr("couch_db")                                   # => -1
r.incrby("redis_db", 99)                             # => 100
r.decrby("couch_db", -101)                           # => 100

# Expiration
r.expire("redis_db", 100)                            # => true
r.expireat("redis_db", Time.now.to_i + 30)           # expire in 30 seconds

# Hashes
r.hset("hash_dt", "key1", true)                      # => true
r.hget("hash_dt", "key1")                            # => "true"
r.hmset("hash_dt", :key2, "value2", :key3, "value3") # => OK
r.hvals("hash_dt")                                   # => ["true", "value2", "value3"]
r.hlen("hash_dt")                                    # => 3

# Limit & Offset
r.zrangebyscore("key", "-inf", "+inf", :limit => [0, 1])

# WITHSCORES
r.zrangebyscore("key", "-inf", "+inf", :with_scores => true)
