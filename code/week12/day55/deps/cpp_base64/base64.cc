#include "base64.h"

#include <cstring>
#include <iostream>

namespace base64 {
	static const char base64_encode_table[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/'
	};

	static const char base64_decode_table[] = {
	};

	std::string encode(const std::string& src)
	{
		std::string result((src.length()+2) / 3 * 4, '\0');
		const char* src_data = src.data();
		int left_bytes = static_cast<int>(src.length());
		unsigned int pos = 0;
		int base64_encode_table_pos = 0;

		for (; left_bytes >= 3; left_bytes -= 3, src_data += 3) {
			base64_encode_table_pos = (src_data[0] & 0xfc) >> 2;
			result[pos++] = base64_encode_table[base64_encode_table_pos]; // 1

			base64_encode_table_pos = ((src_data[0] & 0x03) << 4) + ((src_data[1] & 0xf0) >> 4);
			result[pos++] = base64_encode_table[base64_encode_table_pos]; // 2

			base64_encode_table_pos = ((src_data[1] & 0x0f) << 2) + ((src_data[2] & 0xc0) >> 6);
			result[pos++] = base64_encode_table[base64_encode_table_pos]; // 3

			base64_encode_table_pos = src_data[2] & 0x3f;
			result[pos++] = base64_encode_table[base64_encode_table_pos]; // 4
		}

		switch (left_bytes) {
			case 2:
				base64_encode_table_pos = (src_data[1] & 0x0f) << 2;
				result[pos+2] = base64_encode_table[base64_encode_table_pos]; // 3
			case 1:
				result[pos+3] = '='; //4

				if (left_bytes == 1) {
					result[pos+2] = '=';
					base64_encode_table_pos = (src_data[0] & 0x03) << 4;
				}
				result[pos+1] = base64_encode_table[base64_encode_table_pos]; // 2

				base64_encode_table_pos = (src_data[0] & 0xfc) >> 2;
				result[pos] = base64_encode_table[base64_encode_table_pos]; // 1
			case 0:
			default:
				break;
		}

		return result;
	}

	std::string decode(const std::string& src)
	{
	}
}
