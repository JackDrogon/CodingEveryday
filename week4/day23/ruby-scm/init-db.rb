#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

sha1_dir = ".dircache/objects"
begin
  Dir.mkdir '.dircache', 0700
rescue
  
end

def mkdir(dirname)
  begin
    Dir.mkdir dirname, 0700
  rescue
    
  end
end

mkdir sha1_dir
0.upto(255) { |i|
  path = sha1_dir + sprintf("/%02x", i)
  mkdir path
}
