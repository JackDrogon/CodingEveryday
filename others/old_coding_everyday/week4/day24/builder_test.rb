#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

require 'builder'

xml = Builder::XmlMarkup.new(:target=>STDOUT, :indent=>2)
xml.em("emphasized")
xml.em { xml.b("emph & bold") }
xml.a("A Link", "href" => "http://rubyonrails.org")
xml.target("name" => "compile", "option" => "fast")

xml.target
