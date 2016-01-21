#include "base64.h"

#include <cstring>
#include <iostream>

namespace base64 {
	static const char base64_table[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', '0', '1', '2', '3',
		'4', '5', '6', '7', '8', '9', '+', '/'
	};

	std::string encode(std::string& src)
	{
		if (!src.length()) {
			return std::string();
		}

		// struct __attribute__ ((__packed__)) {
		// 	char a:6;
		// 	char b:6;
		// 	char c:6;
		// 	char d:6;
		// } buf;
		int base64_table_pos;
		// std::string result(src.length() * 2, '\0');
		std::string result((src.length()+2) / 3 * 4, '\0');
		std::cout << "src length:  " << src.length() << " , result length: " << result.length() << std::endl;
		const char* src_data = src.data();
		// int buf[4];
		int left_bytes = src.length();
		unsigned int pos = 0;
		unsigned int copy_bytes = 0;

		while (left_bytes > 0) {
			std::cout << src_data << std::endl;
			if (left_bytes < 3) {
				copy_bytes = left_bytes;
			} else {
				copy_bytes = 3;
			}
			switch (copy_bytes) {
				case 1:
					base64_table_pos = (src_data[0] & 0xfc) >> 2;
					result[pos++] = base64_table[base64_table_pos];

					base64_table_pos = (src_data[0] & 0x03) << 4;
					result[pos++] = base64_table[base64_table_pos];

					result[pos++] = '=';
					result[pos++] = '=';
				case 2:
					base64_table_pos = (src_data[0] & 0xfc) >> 2;
					result[pos++] = base64_table[base64_table_pos];

					base64_table_pos = ((src_data[0] & 0x03) << 4) + ((src_data[1] & 0xf0) >> 4);
					result[pos++] = base64_table[base64_table_pos];

					base64_table_pos = (src_data[1] & 0x0f) << 2;
					result[pos++] = base64_table[base64_table_pos];

					result[pos++] = '=';
				case 3:
					base64_table_pos = (src_data[0] & 0xfc) >> 2;
					result[pos++] = base64_table[base64_table_pos];

					base64_table_pos = ((src_data[0] & 0x03) << 4) + ((src_data[1] & 0xf0) >> 4);
					result[pos++] = base64_table[base64_table_pos];

					base64_table_pos = ((src_data[1] & 0x0f) << 2) + ((src_data[2] & 0xc0) >> 6);
					result[pos++] = base64_table[base64_table_pos];

					base64_table_pos = src_data[2] & 0x3f;
					result[pos++] = base64_table[base64_table_pos];
				default:
					break;
			}

			src_data += 3; // 此处就算超了也没关系，因为src_data不会再用了
			left_bytes -= 3;
		}

		return result;
	}
}
