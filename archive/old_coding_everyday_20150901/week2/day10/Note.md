1. 关于ruby的json使用
	ruby使用JSON.parse的时候，如果是parse一个json数组， 比如:
```ruby
require 'json'
json = JSON.parse('{[1, 2, 3]}')
```
	这个时候json[0]就是1， json[2]就是3。如果要迭代输出，直接json.each即可。



2. 关于ruby http的使用
```
require 'net/http'
Net::HTTP.get('example.com', '/index.html') # => String

uri = URI('http://example.com/index.html?count=10')
Net::HTTP.get(uri) # => String
```

关于uri这个倒是可以研究一下，看见过redis uri， 在lamernews中
```ruby
RedisURL = "redis://127.0.0.1:10000"
```
