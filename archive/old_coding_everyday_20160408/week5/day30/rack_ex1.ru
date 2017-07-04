#!/usr/bin/env ruby

require 'rack'
#load 'request_controller.rb'

class RequestController
  def call(env)
    p env
    [200, {}, ["Hello World"]]
  end
end

Rack::Handler::WEBrick.run(
  RequestController.new,
  :Port => 9000
)
