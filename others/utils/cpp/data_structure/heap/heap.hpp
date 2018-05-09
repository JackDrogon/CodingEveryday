#pragma once

#include <stddef.h> /* NULL */

// TODO: not completed

namespace nepenthe {

namespace data_structure {

struct HeapNode {
	struct HeapNode *left;
	struct HeapNode *right;
	struct HeapNode *parent;
};

class Heap {
public:
private:
};


} // data_structure

} // nepenthe
