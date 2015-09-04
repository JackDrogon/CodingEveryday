#!/usr/bin/env lua
-- -*- coding:utf-8 -*-

function main()
	co = coroutine.create(function () print "hi" end)
	print(co)
	print(coroutine.status(co))
	coroutine.resume(co)
	print(coroutine.status(co))
end

main()
