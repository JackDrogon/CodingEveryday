#!/usr/bin/env osascript -l JavaScript

ObjC.import("stdlib")
ObjC.import("stdio")

puts = $.puts
exit = $.exit


function chrome_name() {
	return "/Applications/Google\ Chrome\ Canary.app/"
}

var chrome = Application(chrome_name())
var count = 0

chrome.windows().forEach(function(window) {
	count += window.tabs().length
})

puts(count)
exit(0)
