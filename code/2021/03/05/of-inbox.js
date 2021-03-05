#!/usr/bin/env osascript -l JavaScript

ObjC.import("stdlib")

exit = $.exit

var of = Application("OmniFocus")

// puts(of.defaultDocument.inboxTasks[3].name())

var inboxTasks = []
of.defaultDocument.inboxTasks().forEach(function(task) {
	inboxTasks.push({id: task.id(), name: task.name(), note: task.note()})
})
console.log(JSON.stringify(inboxTasks))

exit(0)
