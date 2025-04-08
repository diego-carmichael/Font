#include "general/string.hpp"

#include "dbg/log.hpp"

namespace str {
	int readUTF8(std::vector<uint8_t> data, std::string* s) {
		for (size_t c = 0; c < data.size(); ++c) {
			if (data[c] > 0x007F) {
				dbg::log("Non-ASCII string! This version of Font does not support that.\n");
				return -1;
			}
			s->push_back(data[c]);
		}
		return 0;
	}

	void writeUTF8(std::vector<uint8_t>* data, std::string s) {
		for (size_t c = 0; c < s.length(); ++c) {
			data->push_back(s[c]);
		}
	}
}