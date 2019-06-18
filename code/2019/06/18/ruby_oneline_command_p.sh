#!/bin/sh

seq 10 | paste -sd, | ruby -pe 'sub(/,/, " : ")'
seq 10 | paste -sd, | ruby -pe 'gsub(/,/, " : ")'
