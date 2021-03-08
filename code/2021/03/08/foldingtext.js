#!/usr/bin/env osascript -l JavaScript

// command line: save/open/create
// today.ft

var ft = Application("/Applications/FoldingText.app")

const FILE_PREFIX = "/Users/Nepenthe/Library/Mobile Documents/com~hogbaysoftware~TaskPaper/Documents"
var files = ["now.ft", "done.ft", "review.ft", "toolbox.ft"]

function open() {
	files.forEach(function(file) {
		file = FILE_PREFIX + "/" + file
		console.log(file)
		ft.open(file)
	})
}

function save() {
	var windows = ft.windows()
	windows.forEach(function(window) {
		console.log("Save " + window.name())
		ft.save(window)
	})
}

save()
