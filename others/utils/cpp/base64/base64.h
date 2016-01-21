#ifndef BASE64_H_
#define BASE64_H_

#include <string>

// TODO: Add mime_encode && mime_decode
// TODO: Think about decode BAD error && = in middle problem(ex: "\t       SGVsbG\t     8s================V29ybGQh\t=======")

namespace base64 {
	std::string encode(const std::string& src);
	std::string decode(const std::string& src);
} // namespace base64

#endif // BASE64_H_
