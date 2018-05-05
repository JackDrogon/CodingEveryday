#include "pidfile.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	(void) argc;
	pidfile_write();
	pidfile_write(std::string(argv[0]) + ".pid");
	cout << pidfile_read() << endl;
}
