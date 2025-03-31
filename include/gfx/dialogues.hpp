#pragma once

#include <string>
#include <vector>

namespace gfx {
	typedef struct fileFormatInfo fileFormatInfo;
	struct fileFormatInfo {
		std::string name;
		std::string extension; // Without the '.', "" for all files
	};

	typedef struct fileMenu fileMenu;
	struct fileMenu {
		std::vector<fileFormatInfo> fileFormats;
	};
}