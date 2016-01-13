# coding: utf-8
# vim:filetype=ruby:

God.watch do |w|
  w.name = "simple"
  w.start = "ruby ./simple.rb"
  w.keepalive
end
