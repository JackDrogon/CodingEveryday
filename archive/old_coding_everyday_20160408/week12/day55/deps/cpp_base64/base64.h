#ifndef BASE64_H_
#define BASE64_H_

#include <string>

namespace base64 {
	std::string encode(const std::string& src);
	std::string decode(const std::string& src);
} // base64

#endif // BASE64_H_
