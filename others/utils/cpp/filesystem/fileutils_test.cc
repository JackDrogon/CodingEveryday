#include "fileutils.h"

#include <iostream>

using namespace std;
using namespace nepenthe::filesystem::fileutils;

int main(int argc, char **argv)
{
	if (argc < 2) {
		cerr << argv[0] << " <filename>" << endl;
		exit(1);
	}

	char *name = argv[1];
	printf("exists: %s\n", file_exists(name) ? "yes" : "no");
	printf("size: %lld\n", file_size(name));

	if (file_exists(name))
		puts(file_read(name));

	char path[] = "/tmp/long/dir/sequence";
	file_mkdir_p(path);
	printf("'%s' %s\n", path,
	       file_exists(path) ? "created" : "not created");

	return 0;
}
