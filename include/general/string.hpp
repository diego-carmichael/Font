#pragma once

// Because this version of Font only supports ASCII,
// these functions don't REALLY do what they say, they
// just return bad values if anything isn't ASCII.

#include <string>
#include <vector>
#include <cstdint>

namespace str {
	int readUTF8(std::vector<uint8_t> data, std::string* s);
	void writeUTF8(std::vector<uint8_t>* data, std::string s);
}