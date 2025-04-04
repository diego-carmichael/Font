#pragma once

#include "gfx/surface.hpp"
#include "create/logic/action.hpp"
#include "create/logic/canvas.hpp"
#include "general/event.hpp"
#include "create/logic/glyph.hpp"

#include <string>

namespace fnt {
	class font {
	public:
		font(void);
		
		canvas cv;
		std::string name;

		cr::actionSet actionSet;
		cr::action action;

		std::vector<glyph> glyphs;
		size_t currentGlyph;

	public:
		ev::event onActionChange {}; // (actionDesc prevAction)
		void changeAction(cr::actionSet actionSet, cr::action action);

	public:
		void glyphToShape(glyph* g, gfx::shape* s, gfx::rect coverage);
	};

	extern font currentFont;
	extern std::string currentPath;
	void loadCurrentFont(void);
	void saveCurrentFont(gfx::surface* sf);

	void openFontButton(void* data); // gfx::surface*
	void saveFontButton(void* data); // gfx::surface*
}