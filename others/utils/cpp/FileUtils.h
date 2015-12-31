// coding: utf-8

#ifndef _FILEUTILS_H__
#define _FILEUTILS_H__

#include <string>
#include <cstdint>

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

#endif // _FILEUTILS_H__
