proc getLines {fp} {
  while {[gets $fp line]>=0} {
    puts $line
  }

  if {0 && [eof $fp]} {
    puts "DEBUG: EOF [tell $fp]"
  }
  if {0 && [fblocked $fp]} {
    puts "DEBUG: BLOCKED [tell $fp]"
  }
  after 1000
}

set file [lindex $argv 0]
set fp [open $file r]
fconfigure $fp -block 0
fileevent $fp readable [list getLines $fp]

vwait forever
