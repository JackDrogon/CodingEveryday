#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

void fun()
{
}

int main(int argc, char* argv[])
{
	assert(argc > 1);

	int n = atoi(argv[1]);
	for (int i = 0; i < n; ++i) {
		fun();
	}
	
	return 0;
}
