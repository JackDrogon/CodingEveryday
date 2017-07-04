#include "FileUtils.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>

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

	return  mkdir(dirname.data(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
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
