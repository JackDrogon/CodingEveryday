-- 八皇后 （实际为了增加搜索，这里是10皇后）

function queen(d, n)
	local i, j, c
	i = 1
	if n == 1 then d.total = 0 end
	for i = 1, 10 do
		c = true
		for j = 1, (n - 1) do
			if (d[j] == i) or (math.abs(d[j] - i) == n - j) then
				c = false
			end
		end
		if c and n == 10 then
			d.total = d.total + 1
			--print ('search', d.total)
		elseif c then
			d[n] = i
			queen(d, n + 1)
		end
	end
	return d.total
end

queen({}, 1)

t = os.clock()

for i = 1, 10 do
	queen({}, 1)
end

print (os.clock() - t)
