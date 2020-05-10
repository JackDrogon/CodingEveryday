#pragma once

#include <list>
#include <unordered_map>
#include <sstream>

namespace nepenthe
{
namespace data_structure
{
// TODO: Add comments
// TODO: capicity && resize... hash_map && list malloc memery when construct
// TODO: Add size_type
template <typename Key, typename Value> class LRU;
template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &stream, const LRU<Key, Value> &c);

template <typename Key, typename Value> class LRU {
    public:
	explicit LRU(unsigned int capacity) : capacity_(capacity)
	{
	}

	void put(const Key &key, const Value &value)
	{
		auto value_iter = values_.find(key);
		if (value_iter == values_.end()) {
			insert(key, value);
		} else {
			value_iter->second.first = value;
			use(&(value_iter->second));
		}
	}

	// TODO: override const: mutable
	bool get(const Key &key, Value &value)
	{
		auto value_iter = values_.find(key);
		if (value_iter != values_.end()) {
			use(&(value_iter->second));
			value = value_iter->second.first;
			return true;
		}

		return false;
	}

	void remove(const Key &key)
	{
		auto value_iter = values_.find(key);
		if (value_iter == values_.end())
			return;

		values_.erase(value_iter);
		keys_.erase(value_iter->second.second);
	}

	unsigned int Capacity() const
	{
		return capacity_;
	}

    private:
	using list = std::list<Key>;
	// using value = std::pair<Value, typename list::iterator>;
	using map =
		std::unordered_map<Key,
				   std::pair<Value, typename list::iterator>>;

    private:
	// Not copyable, not assignable.
	LRU(const LRU &) = delete;
	LRU &operator=(const LRU &) = delete;

	void evict()
	{
		auto value_iter = values_.find(keys_.front());
		values_.erase(value_iter);
		keys_.pop_front();
	}

	void insert(const Key &key, const Value &value)
	{
		if (keys_.size() == capacity_) {
			evict();
		}

		auto key_iter = keys_.insert(keys_.end(), key);
		values_[key] = std::make_pair(value, key_iter);
	}

	void use(typename map::mapped_type *value)
	{
		// Move the "pointer" to the end of the lru list.
		keys_.splice(keys_.end(), keys_, value->second);

		// Now update the "pointer" so we can do this again.
		value->second = --keys_.end();
	}

	// Give the operator access to our internals.
	// clang-format off
		friend std::ostream &operator<< <>(std::ostream &stream,
						  const LRU &c);
	// clang-format on

	unsigned int capacity_;
	list keys_;
	map values_;
};

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &stream, const LRU<Key, Value> &c)
{
	for (auto &&key : c.keys_) {
		stream << key << ": ";
		auto it = c.values_.find(key);
		stream << it->second.first << '\n';
	}
	return stream;
}
} // namespace data_structure
} // namespace nepenthe
