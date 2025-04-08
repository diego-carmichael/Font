#pragma once

#include "gfx/surface.hpp"
#include "create/logic/action.hpp"
#include "create/logic/canvas.hpp"
#include "general/event.hpp"
#include "create/logic/glyph.hpp"

#include <string>

namespace fnt {
	typedef struct fontData fontData;
	struct fontData {
		std::string name;
		std::vector<glyph> glyphs;
		size_t currentGlyph;
	};
	void defaultFontData(fontData* data);

	class font {
	public:
		font(void);
		fontData data;
		canvas cv;

	public:
		cr::actionState acState;
		ev::event onActionChange {}; // (actionState* prevState)
		void changeAction(cr::actionState state);

	public:
		void glyphToShape(glyph* g, gfx::shape* s, gfx::rect coverage);
	};

	extern font currentFont;
	extern std::string currentPath;
	void loadCurrentFont(std::string filename);
	void saveCurrentFont(std::string filename);

	void openFontButton(void* data); // gfx::surface*
	void saveFontButton(void* data); // gfx::surface*

	int openFile(const char* filename, fontData* fdata, canvasData* cdata);
	int saveFile(const char* filename, fontData* fdata, canvasData* cdata);
	extern ev::event onFontOpen; // (0)
	extern ev::event onFontClose; // (0)
}