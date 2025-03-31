#pragma once

#include "gfx/surface.hpp"
#include "create/logic/action.hpp"
#include "create/logic/canvas.hpp"

#include <string>

namespace fnt {
	class font {
	public:
		font(void);
		
		canvas cv;
		std::string name;
		cr::actionSet actionSet;
		cr::action action;
	};

	extern font currentFont;
	extern std::string currentPath;
	void loadCurrentFont(void);
	void saveCurrentFont(gfx::surface* sf);

	void openFontButton(void* data); // gfx::surface*
	void saveFontButton(void* data); // gfx::surface*
}