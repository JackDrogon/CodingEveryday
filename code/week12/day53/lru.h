#ifndef LRU_H_
#define LRU_H_

#include <list>
#include <unordered_map>
#include <utility>
// #include <ostream>

// TODO: Add comments
// TODO: capicity && resize... hash_map && list malloc memery when construct
// TODO: NoCopyable
// TODO: Add size_type

template<typename Key, typename Value>
class LRU {
public:
	using list = std::list<Key>;
	using map = std::unordered_map<
		Key, std::pair<Value, typename list::iterator> >;
	
	explicit LRU(unsigned int capacity) :
		capacity_(capacity), keys_(capacity), values_(capacity) {}

	void put(const Key& key, const Value& value)
	{
		auto value_iter = values_.find(key);
		if (value_iter == values_.end()) {
			insert(key, value);
		} else {
			value_iter->second.first = value;
			use(value_iter);
		}
	}

	bool get(const Key& key, Value& value)
	{
		auto value_iter = values_.find(key);
		if (value_iter != values_.end()) {
			use(value_iter);
			value = value_iter->second->first;
			return true;
		}

		return false;
	}

	unsigned int Capacity() { return capacity_; }

private:
	unsigned int capacity_;
	list keys_;
	map values_;

	void evict()
	{
		auto value_iter = values_.find(keys_.front());
		values_.erase(value_iter);
		keys_.pop_front();
	}

	void insert(const Key& key, const Value& value)
	{
		if (keys_.size() > capacity_) {
			evict();
		}

		auto key_iter = keys_.insert(key);
		values_[key] = std::make_pair(value, key_iter);
	}

	void use(typename map::iterator value_iter)
	{
		// Move the "pointer" to the end of the lru list.
		keys_.splice(keys_.end(), keys_, value_iter->second.second);

		// Now update the "pointer" so we can do this again.
		value_iter->second.second = --keys_.end();
	}

	// Give the operator access to our internals.
	// friend std::ostream& operator << <>(
	// 		std::ostream& stream,
	// 		const cache<Key, Value>& c);

};

#endif // LRU_H_
