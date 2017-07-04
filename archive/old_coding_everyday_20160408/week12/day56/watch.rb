#!/usr/bin/env ruby
# -*- coding:utf-8 -*-

USAGE = <<EOF
  Usage: #{__FILE__} [options] <cmd>

  Options:

    -q, --quiet           only output stderr
    -x, --halt            halt on failure
    -i, --interval <n>    interval in seconds or ms defaulting to 1
    -v, --version         output version number
    -h, --help            output this help information
EOF

if ARGV.size == 0
  puts USAGE
  exit 1
end

loop {
  sleep(1)
  begin
    result = `#{ARGV.join " "}`
  rescue
    
  end
  puts result if $?.success?
}
