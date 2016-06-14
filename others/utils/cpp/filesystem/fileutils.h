// coding: utf-8

#ifndef FILEUTILS_H_
#define FILEUTILS_H_

#pragma once

#include <string>
#include <cstdint>

namespace nepenthe {

namespace filesystem {

namespace fileutils {

// TODO: 参考shell的test命令
// TODO: 参考Ruby && Erlang

bool is_dir(std::string& dirname);
bool is_file(std::string& filename);
bool mkdir(std::string& dirname);
bool mkdir_p(std::string& dirname);
bool rmdir(std::string& dirname);
bool rmdir_f(std::string& dirname);
bool chdir(std::string& dirname);
bool chmod(std::string& filename, int mode);
bool cp(std::string& orig, std::string& dest);
uint64_t du(const std::string& filename);

off_t file_size(const char *filename);
int file_exists(const char *filename);
char *file_read(const char *filename);
void file_mkdir_p(std::string path);
// rm -rf

} // fileutils

} // filesystem

} // nepenthe

#endif // FILEUTILS_H_
