#include "fileutils.h"

#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>

// TODO: Refer to clib fs

namespace nepenthe {

namespace filesystem {

namespace fileutils {

bool is_dir(std::string& dirname)
{
	struct stat buf;

	if (dirname.empty()) {
		return false;
	} else if (stat(dirname.data(), &buf)) {
		return buf.st_mode & S_IFDIR;
	} else {
		return false;
	}
}

bool is_file(std::string& filename)
{
	struct stat buf;

	if (filename.empty()) {
		return false;
	} else if (stat(filename.data(), &buf)) {
		// TODO: dir is not file
		return buf.st_mode & S_IFDIR;
	} else {
		return false;
	}
}

bool mkdir(std::string& dirname)
{
	struct stat sb;

	if (dirname.empty()) {
		return false;
	}

	// if it already exists, return.
	if (stat(dirname.data(), &sb) == 0) {
		return true;
	}

	return  ::mkdir(dirname.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
}

bool mkdir_p(std::string& dirname)
{
	// TODO: use badaclient parse...
}

uint64_t du(const std::string& filename)
{
	struct stat statbuf;
	unsigned long long sum;

	if (lstat(filename.c_str(), &statbuf) != 0) {
		return 0;
	}

	// sum = statbuf.st_blocks * statbuf.st_blksize;
	sum = statbuf.st_size;

	if (S_ISLNK(statbuf.st_mode)) {
		if (stat(filename.c_str(), &statbuf) != 0) {
			return 0;
		}
		sum = statbuf.st_size;
	}

	if (S_ISDIR(statbuf.st_mode)) {
		DIR *dir;
		struct dirent *entry;
		std::string newfile;

		dir = opendir(filename.c_str());
		if (!dir) {
			return sum;
		}

		while ((entry = readdir(dir))) {
			if (strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0)
				continue;
			newfile = filename + "/" + entry->d_name;
			sum += du(newfile);
		}
		closedir(dir);
	} else {
		return sum;
	}

	return sum;
}



// Return the filesize of `filename` or -1.
off_t file_size(const char *filename)
{
	struct stat s;
	if (stat(filename, &s) < 0)
		return -1;
	return s.st_size;
}


// Check if `filename` exists.
int file_exists(const char *filename) { return -1 != file_size(filename); }


// Read the contents of `filename` or return NULL.
char *file_read(const char *filename)
{
	off_t len = file_size(filename);
	if (len < 0)
		return NULL;

	char *buf = (char *)malloc(len + 1);
	if (!buf)
		return NULL;

	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return NULL;

	ssize_t size = read(fd, buf, len);
	close(fd);

	if (size != len)
		return NULL;

	return buf;
}

// Recursively creates directories on `path`.
// Returns 1 if somehow couldn't create one.
void file_mkdir_p(std::string path)
{
	if (path.empty()) return;
	size_t len = path.size();
	if (path[len - 1] == '/') path[len - 1] = '\0';

	for (size_t i = 0; i != len ; ++i) {
		if (path[i] == '/') {
			path[i] = '\0';
			::mkdir(path.data(), S_IRWXU);
			path[i] = '/';
		}
	}

	::mkdir(path.data(), S_IRWXU);
}

} // fileutils

} // filesystem

} // nepenthe
