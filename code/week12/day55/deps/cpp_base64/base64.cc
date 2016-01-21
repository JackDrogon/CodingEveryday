#include "base64.h"

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

#define BAD 65
#define WS 66
#define EQ 67
	static const char base64_decode_table[] = {
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,WS,WS,BAD,BAD,WS,BAD, // 1-15
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD, // 16-31
		BAD,WS,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,62,BAD,BAD,BAD, // 32-47
		63,52,53,54,55,56,57,58,59,60,61,BAD,BAD,BAD,EQ,BAD,// 48-63
		BAD,BAD,0,1,2,3,4,5,6,7,8,9,10,11,12,13,
		14,15,16,17,18,19,20,21,22,23,24,25,BAD,BAD,BAD,BAD,
		BAD,BAD,26,27,28,29,30,31,32,33,34,35,36,37,38,39,
		40,41,42,43,44,45,46,47,48,49,50,51,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,
		BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD,BAD
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
		std::string result((src.length()+3) / 4 * 3, '\0');
		const char* src_data = src.data();
		unsigned int pos = 0;
		unsigned int bit_pos = 0;
		int decode_value = 0;

		for (int left_bytes = static_cast<int>(src.length());
				left_bytes != 0; --left_bytes) {
			switch (decode_value = base64_decode_table[static_cast<int>(*src_data++)]) {
				case BAD: case WS: case EQ:
					break;
				default:
					switch (bit_pos) {
						case 0:
							result[pos] = static_cast<char>(decode_value << 2);
							bit_pos = 6;
							break;
						case 2:
							result[pos++] += decode_value;
							bit_pos = 0;
							break;
						case 4:
							result[pos] += decode_value >> 2;
							result[++pos] = static_cast<char>(decode_value << 6);
							bit_pos = 2;
							break;
						case 6:
							result[pos] += decode_value >> 4;
							result[++pos] = static_cast<char>(decode_value << 4);
							bit_pos = 4;
							break;
					}
			}
		}

		result.resize(pos);

		return result;
	}

} // namespace base64
