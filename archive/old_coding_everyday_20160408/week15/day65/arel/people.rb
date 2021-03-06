#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'active_record'
ActiveRecord::Base.logger = Logger.new(STDOUT)
class Person < ActiveRecord::Base
  establish_connection adapter: 'sqlite3', database: 'foobar.db'
  connection.create_table table_name, force: true do |t|
    t.string :name
  end
end

bob = Person.create!(name: 'bob')
puts Person.all.inspect
bob.destroy
puts Person.all.inspect
