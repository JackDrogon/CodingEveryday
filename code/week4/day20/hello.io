#!/usr/bin/env io
# coding: utf-8

"Hello,World!\n" print

Vehicle := Object clone
(2 sin) println # (2 sin) can see Object Oritin -> send message
3 cos println

method("This is a print method." println)

a := 2
if(a == 1) then(writeln("a is one")) else(writeln("a is not one"))
if(a == 1, writeln("a is one"), writeln("a is not one"))

# List
d := List clone append(30, 10, 5, 20)
d size println
d println
d = d sort
d println
d first println
d last println
d at(2) println
d remove(30)
d atPut(1, 123)
list(30, 10, 5, 20) select(>10) println
list(30, 10, 5, 20) detect(>10) println
list(30, 10, 5, 20) map(*2)
list(30, 10, 5, 20) map(v, v*2)

# Loop
for(i, 1, 10, write(i, " "))
d foreach(i, v, writeln(i, ": ", v))
list("abc", "def", "ghi") foreach(println)

# String
a := "foo" println
b := "bar" println
c := a .. b println
c at(0) println
c at(0) asCharacter println
s := "this is a test" println
words := s split(" ", "\t") println
s findSeq("is")
s findSeq("test")
s exSlice(10)
s exSlice(2, 10)
