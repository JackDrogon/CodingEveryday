#ifndef SKIPLIST_H_
#define SKIPLIST_H_

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <random>

namespace nepenthe {

namespace data_structure {

// TODO: Iterator
// TODO: Concurrency

template <typename Key, typename Value>
class SkipList {
private:
	struct Node;

	// No copying allowed
	SkipList(const SkipList &);
	void operator=(const SkipList &);

public:
	SkipList();
	~SkipList();

	// false -> key exist, true -> key don't exist
	bool Set(const Key &key, const Value &value);
	bool Get(const Key &key, Value &value);
	bool Delete(const Key &key);
	void Clear();

private:
	inline struct Node *NewNode(const Key &key, const Value &value , int height) const
	{
		Node *node = static_cast<Node *>(malloc(sizeof(Node) + sizeof(Node *) * height));

		assert(node != NULL);

		return new (node) Node(key, value, height);
	}

	// Return the earliest node that comes at or after key.
	// Return NULL if there is no such node.
	//
	// If prev is non-NULL, fills prev[level] with pointer to previous
	// node at "level" for every level in [0..max_height_-1].
	Node *FindGreaterOrEqual(const Key &key, Node **prev) const;

	int RandomHeight();

private:
	enum { kMaxHeight = 16 };

	size_t size_ = 0;
	Node *head_;
	size_t max_height_;

	std::default_random_engine rnd_;
};

template <typename Key, typename Value>
struct SkipList<Key, Value>::Node {
	explicit Node(const Key &k, const Value &v, int height) : key(k), value(v)
	{
		memset(next, '\0', sizeof(Node *) * height);
	}

	Key const key;
	Value value;
	Node *next[0];
};


template <typename Key, typename Value>
SkipList<Key, Value>::SkipList()
	: size_(0), head_(NewNode(Key(), Value(), kMaxHeight)), max_height_(1), rnd_(std::random_device()())
{
}

template <typename Key, typename Value>
SkipList<Key, Value>::~SkipList()
{
	Clear();
	free(head_);
}

template <typename Key, typename Value>
typename SkipList<Key, Value>::Node *
SkipList<Key, Value>::FindGreaterOrEqual(const Key &key, Node **prev) const
{
	Node *node = head_;
	int level = max_height_ - 1;
	
	while (true) {
		Node *next = node->next[level];
		if (next != NULL && key > next->key) {
			node = next;
		} else {
			if (prev != NULL) prev[level] = node;
			if (level == 0) {
				return next;
			} else {
				--level;
			}
		}
	}
}

template <typename Key, typename Value>
int SkipList<Key, Value>::RandomHeight()
{
	static const unsigned int kBranching = 4;
	int height = 1;
	while (height < kMaxHeight && ((rnd_() % kBranching) == 0)) {
		height++;
	}
	assert(height > 0);
	assert(height <= kMaxHeight);
	return height;
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::Get(const Key &key, Value &value)
{
	Node *node = FindGreaterOrEqual(key, NULL);

	if (node && node->key == key) {
		value = node->value;
		return true;
	} else {
		return false;
	}
}

template <typename Key, typename Value>
bool SkipList<Key, Value>::Set(const Key &key, const Value &value)
{
	Node *prev[kMaxHeight];
	Node *node = FindGreaterOrEqual(key, prev);

	int height = RandomHeight();
	if (node && node->key == key) {
		node->value = value;
		return false;
	} else {
		if (height > max_height_) {
			for (int i = max_height_; i < height; ++i) {
				prev[i] = head_;
			}
		}

		node = NewNode(key, value, height);
		for (int i = 0; i < height; i++) {
			node->next[i] = prev[i]->next[i];
			prev[i]->next[i] = node;
		}

		max_height_ = height;
		return true;
	}
}


template <typename Key, typename Value>
bool SkipList<Key, Value>::Delete(const Key &key)
{
	Node *prev[kMaxHeight];
	memset(prev, '\0', sizeof(prev));
	Node *node = FindGreaterOrEqual(key, prev);

	if (!node) {
		return false;
	} else {
		for (int i = 0; i < max_height_; ++i) {
			if (prev[i]) {
				prev[i]->next[i] = node->next[i];
			}
		}

		free(node);

		while (max_height_ > 1 && head_->next[max_height_] == NULL) {
			--max_height_;
		}

		return true;
	}
}

template <typename Key, typename Value>
void SkipList<Key, Value>::Clear()
{
	Node *node = head_->next[0];
	Node *next;
	while (node != NULL) {
		next = node->next[0];
		free(node);
		node = next;
	}
	max_height_ = 1;
}

} // data_structure

} // nepenthe

#endif // SKIPLIST_H_
