var app = Application.currentApplication()
app.includeStandardAdditions = true

var Finder = Application('Finder')
var selection = [].slice.call(Finder.selection())
var code = prompt('How to modify the name?', 'return name')
var fn = new Function('name', code)

try {

	var tasks = selection.map(function(item) {
		var name = item.name()
		try {
			var target = fn(name)
		} catch (e) {
			throw new Error('Cannot rename "' + name + '": ' + e)
		}
		if (!target) {
			throw new Error('Cannot rename "' + name + '": expression returned empty result')
		}
		return { item: item, from: name, to: target }
	}).filter(function(task) { return task.from != task.to })

	if (tasks.length == 0) throw new Error('No files to rename!')

		var message = 'These files will be renamed:\n\n' +
			tasks.map(function(task) { return '- ' + task.from + ' => ' + task.to }).join('\n')

			if (confirm(message)) {
				tasks.forEach(executeTask)
			}

} catch (e) {
	alert('Error!', String(e))
}

// Recipes from: https://github.com/dtinth/JXA-Cookbook/wiki/User-Interactions

function prompt(text, defaultAnswer) {
	var options = { defaultAnswer: defaultAnswer || '' }
	try {
		return app.displayDialog(text, options).textReturned
	} catch (e) {
		return null
	}
}

function alert(text, informationalText) {
	var options = { }
	if (informationalText) options.message = informationalText
		app.displayAlert(text, options)
}

function confirm(text) {
	try {
		app.displayDialog(text)
		return true
	} catch (e) {
		return false
	}
}

function executeTask(task) {
	task.item.name = task.to
}
