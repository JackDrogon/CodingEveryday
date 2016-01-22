#ifndef BASE64_H_
#define BASE64_H_

#include <string>

// TODO: Add mime_encode && mime_decode
// TODO: Think about decode BAD error && = in middle problem(ex: "\t       SGVsbG\t     8s================V29ybGQh\t=======")
// FIXME: 此处需要在传入encode/decode table的时候注意了，需要BAD 65， WS 66,  EQ 67

namespace base64 {
	extern const char default_base64_encode_table[];
	extern const char default_base64_decode_table[];

	std::string encode(const std::string& src, const char base64_encode_table[] =  default_base64_encode_table);
	std::string decode(const std::string& src, const char base64_decode_table[] =  default_base64_decode_table);
} // namespace base64

#endif // BASE64_H_
