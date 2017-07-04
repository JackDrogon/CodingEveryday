#!/usr/bin/env elixir
# coding: utf-8

defmodule Factorial do
  def fac(0) do
    1
  end

  def fac(n) do
    n * fac(n-1)
  end
end

#IO.puts System.argv
IO.puts Factorial.fac(Integer.parse System.argv[0])
