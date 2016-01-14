#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'logger'

class FooApp < Logger::Application
  def initialize(foo_app, application_specific, arguments)
    super('FooApp') # Name of the application.
  end

  def run
    log(WARN, 'warning', 'my_method1')
    @log.error('my_method2') { 'Error!' }
  end
end

status = FooApp.new(1, 1, 1).start
