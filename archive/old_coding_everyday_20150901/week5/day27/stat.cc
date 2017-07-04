#include <iostream>
#include <cassert>

#include <sys/stat.h>

using namespace std;

void print_stat(struct stat &st);

int main(int argc, char *argv[])
{
	struct stat st;
	assert(argc > 1);
	if (stat(argv[1], &st) < 0)  {
		cerr << "Stat " << argv[1] << ", Error!" << endl;
	} else {
		print_stat(st);
	}

	return 0;
}

void print_stat(struct stat &st)
{
	cout << "Size: " << st.st_size << " bytes."<< endl;
	cout << "Blocks: " << st.st_blocks << "." << endl;
	cout << "Block Size: " << st.st_blksize << " bytes." << endl;
}
