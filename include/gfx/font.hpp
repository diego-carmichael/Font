#pragma once

#include <vector>
#include <string>

namespace gfx {
	typedef struct fontInfo fontInfo;
	struct fontInfo {
		std::wstring name;
		// std::vector<std::wstring> familyNames;
	};

	typedef struct font font;
	struct font {
		void* data;
	};
}