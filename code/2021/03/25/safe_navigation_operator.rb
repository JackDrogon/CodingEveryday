#!/usr/bin/env ruby
# frozen_string_literal: true

pp ''.length
pp nil&.length

pp '1'[0]
pp nil&.[](0)

data = { 'k1' => { 'k2' => { 'k3' => 'v' } } }
pp data.dig('k1', 'k2', 'k3')
pp nil&.[]('k1')&.[]('k2')&.[]('k3')
