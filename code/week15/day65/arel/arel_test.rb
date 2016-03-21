#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'active_record'

ActiveRecord::Base.establish_connection(adapter: "sqlite3", database: ":memory:")

users          = Arel::Table.new(:users, ActiveRecord::Base)
select_manager = users.project(Arel.star)

sql = select_manager.to_sql
puts sql
