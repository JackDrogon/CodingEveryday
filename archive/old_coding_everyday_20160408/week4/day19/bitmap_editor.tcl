#!/bin/sh
# The next line is executed by /bin/sh, but not tcl \
exec wish $0 ${1+"$@"}

##+##########################################################################
#
# bitmap.tcl -- simple bitmap editor
# by Keith Vetter
#
# Revisions:
# KPV Jan 15, 2003 - initial revision
# KPV Mar 06, 2003 - added functions like shift, clear, invert and resize
#
##+##########################################################################
#############################################################################

package require Tk

set S(cell) 10
set S(prog) "Bitmap Editor"
set S(fname) ""

array set bits { 0 0000 1 1000 2 0100 3 1100 4 0010 5 1010 6 0110 7 1110
                 8 0001 9 1001 a 0101 b 1101 c 0011 d 1011 e 0111 f 1111}
set bitmap {
   #define bullet_width  11
   #define bullet_height  9
   static char bullet_bits[] = {
       0x00,0x00, 0x00,0x00, 0x70,0x00, 0xf8,0x00, 0xf8,0x00,
       0xf8,0x00, 0x70,0x00, 0x00,0x00, 0x00,0x00
   }
}
##+##########################################################################
#
# DoDisplay -- sets up our display
#
proc DoDisplay {} {
   wm title . $::S(prog)
   canvas .c -width 500 -height 500 -bd 2 -relief ridge -highlightthickness 0
   .c xview moveto 0 ; .c yview moveto 0

   bind .c <2> [bind Text <2>]                 ;# Enable button 2 paning
   bind .c <B2-Motion> [bind Text <B2-Motion>]

   frame .fctrl -bd 2 -relief ridge
   label .info -text "Left button to set    Right button to clear" -anchor c \
       -bd 2 -relief ridge

   grid .c .fctrl -sticky news -row 0
   grid .info   ^ -sticky ew
   grid rowconfigure . 0 -weight 1
   grid columnconfigure . 0 -weight 1
   DoControl
   DoMenus
   update
}
##+##########################################################################
#
# DoMenus -- sets up our menus
#
proc DoMenus {} {
   . configure -menu [menu .m -tearoff 0]
   .m add cascade -menu [menu .m.file  -tearoff 0] -label "File"  -underline 0
   .m add cascade -menu [menu .m.image -tearoff 0] -label "Image" -underline 0
   .m add cascade -menu [menu .m.help  -tearoff 0] -label "Help"  -underline 0

   .m.file add command -label "New"  -under 0 -command NewBMP
   .m.file add command -label "Open" -under 0 -command OpenBMP
   .m.file add command -label "Save" -under 0 -command SaveBMP
   .m.file add separator
   .m.file add command -label "Copy" -under 0 -command CopyBMP
   .m.file add separator
   .m.file add command -label Exit -under 1 -command exit

   .m.image add command -label "Clear"       -under 0 -command {BitFunc clear}
   .m.image add command -label "Invert"      -under 0 -command {BitFunc invert}
   .m.image add command -label "Shift left"  -under 6 -command {BitFunc sleft}
   .m.image add command -label "Shift right" -under 6 -command {BitFunc sright}
   .m.image add command -label "Shift up"    -under 6 -command {BitFunc sup}
   .m.image add command -label "Shift down"  -under 6 -command {BitFunc sdown}
   .m.image add separator
   .m.image add command -label "Resize"      -under 0 -command ResizeBMP

   .m.help add command -label About -under 0 -command About
}
##+##########################################################################
#
# DoControl -- draws the control panel
#
proc DoControl {} {
   grid rowconfigure .fctrl   0 -minsize 10
   grid rowconfigure .fctrl 100 -weight 1

   frame .fctop
   grid .fctop - - -in .fctrl -row 1
   set row 0
   foreach a {Name Width Height} {
       set a2 [string map {" " ""} [string tolower $a]]
       label .l$a2 -text "$a:"
       entry .e$a2 -textvariable BM($a2) -width 8 -state disabled
       grid .l$a2 .e$a2 -in .fctop -row [incr row]
   }

   image create bitmap ::img::current
   frame .fimg -bd 2 -relief sunken -padx 10 -pady 10
   label .limg -image ::img::current -bg white
   grid rowconfigure .fctrl 40 -minsize 50
   grid .fimg - - -in .fctrl -row 41
   pack .limg -in .fimg -expand 1
}
##+##########################################################################
#
# ShowBMP -- computes grid size then draws in the current bitmap
#
proc ShowBMP {} {
   global S BM

   if {! [info exists BM(raw)]} return

   set w [winfo width .c] ; set h [winfo height .c]
   set cw [expr {int((($w - 20) / $BM(width)))}]
   set ch [expr {int((($h - 20) / $BM(height)))}]
   set S(cell) [expr {$cw < $ch ? $cw : $ch}]
   if {$S(cell) > 40} { set S(cell) 40}
   if {$S(cell) <  5} { set S(cell) 5}

   DrawGrid
   ShowBits
   unset BM(bits)
   ::img::current config -data $BM(raw)        ;# Update current bitmap display
}
##+##########################################################################
#
# ClearBMP -- clears everything for a new bitmap
#
proc ClearBMP {} {
   global BM
   .c delete all
   ::img::current config -data {}
   array unset BM
   foreach arr [array names BM] { set BM($arr) ""}
   update
}
##+##########################################################################
#
# DrawGrid -- draws the grid of rectangles--each one with proper bindings
#
proc DrawGrid {} {
   global BM

   .c delete all
   foreach {l t} [CellXY 0 0] break
   foreach {b r} [CellXY $BM(height) $BM(width)] break
   .c create rect $l $t $b $r -tag outline -width 2

   set bg [.c cget -bg]
   for {set r 0} {$r < $BM(height)} {incr r} {
       for {set c 0} {$c < $BM(width)} {incr c} {
           .c create rect [CellXY $r $c] -tag [list grid c($r,$c)] -fill $bg
           .c bind c($r,$c) <1> [list Click 1 cell $r $c]
           .c bind c($r,$c) <3> [list Click 2 cell $r $c]
       }
   }
   .c config -scrollregion [.c bbox all]
}
##+##########################################################################
#
# Click -- handles left and right mouse click in a grid cell
#
proc Click {btn what row col} {
   global BM
   if {$btn == 1} {                            ;# Set the pixel
       if {$BM(b,$row,$col)} return            ;# Already set
       set BM(b,$row,$col) 1
       ShowBitCell $row $col
   } else {                                    ;# Clear the pixel
       if {! $BM(b,$row,$col)} return          ;# Already cleare
       set BM(b,$row,$col) 0
       .c delete o($row,$col)
   }
   set BM(raw) [UnparseBMP]
   ::img::current config -data $BM(raw)
}
##+##########################################################################
#
# ShowBits -- draws dots in all "on" cells in the current bitmap,
# only valid after ParseBMP fills in the BM(bits) variable.
#
proc ShowBits {} {
   global BM bits

   set row 0
   set col 0
   foreach byte $BM(bits) {
       foreach {n1 n2} [split $byte ""] break  ;# Get each nibble
       foreach bit [split "$bits($n2)$bits($n1)" ""] { ;# Note the endian
           set BM(b,$row,$col) $bit
           if {$bit} {
               ShowBitCell $row $col
           }
           if {[incr col] >= $BM(width)} {     ;# Do we past the last column?
               incr row
               set col 0
               break
           }
       }
   }
}
##+##########################################################################
#
# ShowBitCell -- draws the "on" bit in a specified cell
#
proc ShowBitCell {row col} {
   .c create oval [CellXY $row $col] -fill black -tag [list bit o($row,$col)]
   .c bind o($row,$col) <1> [list Click 1 oval $row $col]
   .c bind o($row,$col) <3> [list Click 2 oval $row $col]
}
##+##########################################################################
#
# CellXY -- returns the coordinates of a grid cell
#
proc CellXY {r c} {
   global S
   set x1 [expr {10 + $c * $S(cell)}]
   set y1 [expr {10 + $r * $S(cell)}]
   set x2 [expr {$x1 + $S(cell)}]
   set y2 [expr {$y1 + $S(cell)}]

   return [list $x1 $y1 $x2 $y2]
}
##+##########################################################################
#
# ParseBMP -- reads the raw bitmap data into our BM data structure
# NB. face.bmp in demo directory had defines for x_hot and y_hot
#
proc ParseBMP {raw} {
   global S BM

   ClearBMP
   set BM(raw) $raw

   while {1} {
       if {! [regexp {\#define\s+(.*)_width}        $raw => BM(name)]} break
       if {! [regexp {\#define\s+.*_width\s*(\d*)}  $raw => BM(width)]} break
       if {! [regexp {\#define\s+.*_height\s*(\d*)} $raw => BM(height)]} break
       regexp {\#define\s+.*_x_hot\s*(\d*)}  $raw => BM(xhot)
       regexp {\#define\s+.*_y_hot\s*(\d*)}  $raw => BM(yhot)

       if {! [regexp {(0x.*)\}}                     $raw => BM(bits)]} break
       if {! [regsub -all {0x|,} $BM(bits) { }              BM(bits)]} break
       if {! [regsub -all {\s+}  $BM(bits) { }              BM(bits)]} break
       set BM(bits) [string tolower $BM(bits)]
       return                                  ;# Everything ok, get out
   }
   ERROR "$S(fname) is not a proper bmp file"
   ClearBMP
}
##+##########################################################################
#
# OpenBMP -- opens and reads a BMP file
#
proc OpenBMP {} {
   global S

   set types { {{BMP Files} {.bmp}} {{All Files} * }}
   set fname [tk_getOpenFile -defaultextension ".bmp" -initialfile $S(fname) \
                  -filetypes $types]
   if {$fname == ""} return
   if {[catch {set FIN [open $fname r]} emsg]} {
       ERROR "Cannot open $fname\n$emsg"
       return
   }
   set raw [read $FIN]
   close $FIN
   set S(fname) $fname
   ParseBMP $raw
   ShowBMP
}
##+##########################################################################
#
# SaveBMP -- saves the current bitmap to a file
#
proc SaveBMP {} {
   global S BM

   if {! [info exists BM(raw)]} return
   set types {{{BMP Files} {.bmp}} {{All Files} *}}
   set fname [tk_getSaveFile -defaultextension ".bmp" -initialfile $S(fname) \
                  -filetypes $types]
   if {$fname == ""} return
   if {[catch {set FOUT [open $fname w]} emsg]} {
       ERROR "Cannot open $fname\n$emsg"
       return
   }
   puts $FOUT $BM(raw)
   close $FOUT
   set S(fname) $fname
}
##+##########################################################################
#
# UnparseBMP -- converts our internal BM into a proper bitmap data string
#
proc UnparseBMP {} {
   global BM
   set name $BM(name)

   set bmp "\#define ${name}_width $BM(width)\n"
   append bmp "\#define ${name}_height $BM(height)\n"
   if {[info exists BM(xhot)]} {
       append bmp "\#define ${name}_x_hot $BM(xhot)\n"
       append bmp "\#define ${name}_y_hot $BM(yhot)\n"
   }
   append bmp "static char ${name}_bits[] = \{\n"

   set bytes {}
   for {set r 0} {$r < $BM(height)} {incr r} {
       for {set c 0} {$c < $BM(width)} {incr c 8} {
           set byte 0
           for {set cc [expr {$c + 7}]} {$cc >= $c} {incr cc -1} {
               set byte [expr {2 * $byte}]
               if {[info exists BM(b,$r,$cc)] && $BM(b,$r,$cc)} {
                   incr byte
               }
           }
           lappend bytes [format 0x%02x $byte]
       }
   }
   append bmp "    " [join $bytes ", "]
   append bmp "\n\}"

   return $bmp
}
##+##########################################################################
#
# CopyBMP -- copies current bitmap to the clipboard
#
proc CopyBMP {} {
   global BM S

   if {! [info exists BM(raw)]} return
   clipboard clear
   clipboard append $BM(raw)
   tk_messageBox -icon info -title "$S(prog) Info" \
       -message "Bitmap copied to the clipboard"

}
##+##########################################################################
#
# NewBMP -- creates a blank, new bitmap with sizes specified by the user
#
proc NewBMP {} {
   global BM

   set n [NewDlg]
   if {$n == {}} return
   foreach {name width height} $n break

   ClearBMP
   set BM(name)   $name
   set BM(width)  $width
   set BM(height) $height

   for {set r 0} {$r < $BM(height)} {incr r} {
       for {set c 0} {$c < $BM(width)} {incr c} {
           set BM(b,$r,$c) 0
       }
   }
   ParseBMP [UnparseBMP]
   ShowBMP
}
proc ResizeBMP {} {
   global BMP
   set n [NewDlg 1]
   if {$n == {}} return

   foreach {. nwidth nheight} $n break
   WidenBMP $nwidth
   HeightenBMP $nheight

   ParseBMP [UnparseBMP]
   ShowBMP
}
proc WidenBMP {nwidth} {
   global BM
   if {$BM(width) == $nwidth} return
   if {$nwidth > $BM(width)} {
       foreach {low high delete} [list $BM(width) $nwidth 0] break
   } else {
       foreach {low high delete} [list $nwidth $BM(width) 1] break
   }
   for {set row 0} {$row < $BM(height)} {incr row} {
       for {set col $low} {$col < $high} {incr col} {
           set BM(b,$row,$col) 0
           if {$delete} {
               unset BM(b,$row,$col)
           }
       }
   }
   set BM(width) $nwidth
}
proc HeightenBMP {nheight} {
   global BM
   if {$BM(height) == $nheight} return
   if {$nheight > $BM(height)} {
       foreach {low high delete} [list $BM(height) $nheight 0] break
   } else {
       foreach {low high delete} [list $nheight $BM(height) 1] break
   }
   for {set col 0} {$col < $BM(width)} {incr col} {
       for {set row $low} {$row < $high} {incr row} {
           set BM(b,$row,$col) 0
           if {$delete} {
               unset BM(b,$row,$col)
           }
       }
   }
   set BM(height) $nheight
}
##+##########################################################################
#
# NewDlg -- asks the user for bitmap parameters
#
proc NewDlg {{resize 0}} {
   global S NEW BM

   destroy  .new
   toplevel .new -padx 10 -pady 5
   wm title .new "New Bitmap"
   if {$resize} {wm title .new "Resize Bitmap"}
   wm geom .new "+[expr {[winfo x .] + 150}]+[expr {[winfo y .] + 100}]"

   set NEW(ok) 0
   set NEW(width) $BM(width)
   set NEW(height) $BM(height)

   frame .new.top -bd 2 -relief raised -padx 10 -pady 10
   grid columnconfigure .new.top 1 -weight 1
   set widgets {name width height}
   if {$resize} {
       set NEW(name) "xx"
       set widgets {width height}
   }
   foreach a $widgets {
       set a1 [string totitle $a]
       label .new.l$a -text "$a1:"
       entry .new.e$a -textvariable NEW($a)
       grid  .new.l$a .new.e$a -in .new.top -sticky ew
   }

   frame  .new.buttons
   button .new.ok     -text Ok     -width 10 -command ValidForm
   button .new.cancel -text Cancel -width 10 -command {destroy .new}

   pack .new.buttons -side bottom -pady 10
   pack .new.top -side top -fill x
   pack .new.cancel .new.ok -in .new.buttons -side right -padx 10 -expand 1

   raise .new
   set w ".new.e[lindex $widgets 0]"
   focus $w
   $w icursor end
   $w selection range 0 end
   tkwait window .new
   if {$NEW(ok)} {
       return [list $NEW(name) $NEW(width) $NEW(height)]
   }
   return {}
}
##+##########################################################################
#
# ValidForm -- validates the NewDlg and then destroys it if it is ok
#
proc ValidForm {} {
   global NEW

   foreach n {name width height} {
       set NEW($n) [string trim $NEW($n)]
       if {$NEW($n) == ""} return
   }
   if {![string is integer $NEW(width)]} return
   if {![string is integer $NEW(height)]} return

   set NEW(ok) 1
   destroy .new
}
proc ERROR {msg} {
   tk_messageBox -icon error -title "$::S(prog) Error" -message $msg
}
proc About {} {
   set msg "$::S(prog)\n\nby Keith Vetter\nJanuary 2003"
   tk_messageBox -title "About $::S(prog)" -message $msg -icon info
}

proc BitFunc {what} {
   global BM

   if {$what == "clear"} {
       foreach arr [array names BM b,*] {
           set BM($arr) 0
       }
   } elseif {$what == "invert"} {
       foreach arr [array names BM b,*] {
           set BM($arr) [expr {! $BM($arr)}]
       }
   } elseif {$what == "sleft"} {               ;# Shift left
       for {set col 0} {$col < $BM(width)} {incr col} {
           set col2 [expr {$col + 1}]
           for {set row 0} {$row < $BM(height)} {incr row} {
               if {[info exists BM(b,$row,$col2)]} {
                   set BM(b,$row,$col) $BM(b,$row,$col2)
               } else {
                   set BM(b,$row,$col) 0
               }
           }
       }
   } elseif {$what == "sright"} {              ;# Shift right
       for {set col [expr {$BM(width) - 1}]} {$col >= 0} {incr col -1} {
           set col2 [expr {$col - 1}]
           for {set row 0} {$row < $BM(height)} {incr row} {
               if {[info exists BM(b,$row,$col2)]} {
                   set BM(b,$row,$col) $BM(b,$row,$col2)
               } else {
                   set BM(b,$row,$col) 0
               }
           }
       }
   } elseif {$what == "sup"} {                 ;# Shift up
       for {set row 0} {$row < $BM(height)} {incr row} {
           set row2 [expr {$row + 1}]
           for {set col 0} {$col < $BM(width)} {incr col} {
               if {[info exists BM(b,$row2,$col)]} {
                   set BM(b,$row,$col) $BM(b,$row2,$col)
               } else {
                   set BM(b,$row,$col) 0
               }
           }
       }
   } elseif {$what == "sdown"} {               ;# Shift down
       for {set row [expr {$BM(height) - 1}]} {$row >= 0} {incr row -1} {
           set row2 [expr {$row - 1}]
           for {set col 0} {$col < $BM(width)} {incr col} {
               if {[info exists BM(b,$row2,$col)]} {
                   set BM(b,$row,$col) $BM(b,$row2,$col)
               } else {
                   set BM(b,$row,$col) 0
               }
           }
       }
   }
   set BM(raw) [UnparseBMP]
   RedrawBits
   ::img::current config -data $BM(raw)

}
proc RedrawBits {} {
   global BM

   .c delete bit
   for {set row 0} {$row < $BM(height)} {incr row} {
       for {set col 0} {$col < $BM(width)} {incr col} {
           if {$BM(b,$row,$col)} {ShowBitCell $row $col}
       }
   }
}

################################################################
################################################################
################################################################

DoDisplay
ParseBMP $bitmap
ShowBMP
