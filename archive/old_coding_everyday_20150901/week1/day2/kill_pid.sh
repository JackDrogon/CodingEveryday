#!/bin/sh

pid=$(cat "$1.pid")
kill -9 "$pid"
