#!/usr/bin/env osascript -l JavaScript

ObjC.import("stdlib")
ObjC.import("stdio")

puts = $.puts
exit = $.exit


function chrome_name() {
	return "/Applications/Google\ Chrome\ Canary.app/"
}

var chrome = Application(chrome_name())

chrome.windows().forEach(function(window){
	puts("## Window Index: " + window.index() + ", " + window.tabs().length + " tabs")
	window.tabs().forEach(function(tab){
		puts("\t* [" +tab.name() + "]" + "(" + tab.url() + ")")
	})
	puts("")
})
// chrome.windows[0].tabs.push(chrome.Tab({url: "https://www.baidu.com"}))

// puts(JSON.stringify(chromeJson))
exit(0)
