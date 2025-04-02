#pragma once

#include "general/event.hpp"
#include "gfx/defs.hpp"
#include "gfx/menu.hpp"
#include "gfx/dialogues.hpp"
#include "gfx/input.hpp"
#include "gfx/font.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace gfx {
	class surface {
	public:
		void* data;
	public:
		// Might not get the requested width/height!
		surface(std::string name, uint32_t width, uint32_t height);
		~surface(void);

		bool active(void);
		// This call can block!
		void update(void);

		void flagRender(void);

		void getDimensions(uint32_t* width, uint32_t* height);
		// setDimensions(uint32_t width, uint32_m height);
		void setName(std::string name);

	public:
		void setMenu(std::vector<menu> mn);
		void setRightClickMenu(std::vector<menu> mn);
		std::string dialogueOpenFile(fileMenu* mn); // Returns "" on failure
		std::string dialogueSaveFile(fileMenu* mn); // Returns "" on failure

	public:
		ev::event onRender {};
		ev::event onResize {};
		ev::event onKeyPress {}; // (size_t)gfx::inp::keyboardKey
		ev::event onKeyRelease {}; // (size_t)gfx::inp::keyboardKey
		ev::event onMousePress {}; // (size_t)gfx::inp::mouseButton
		ev::event onMouseRelease {}; // (size_t)gfx::inp::mouseButton
		ev::event onCursorMove {}; // (void*)float[2]
		ev::event onCursorScroll {}; // (void*)float[1]
		// ^ 1.f represents a "full scroll", + means up, - means down

		ev::event onRightClickMenuAppearing {}; // 0

	public:
		bool isKeyDown(gfx::inp::keyboardKey key);
		bool isMouseDown(gfx::inp::mouseButton button);

		void getMousePos(float* x, float* y);

	public:
		// == Must only be called in listening to onRender ==
		void renderRect(rect r, col color);
		void renderLine(point p0, point p1, col color);
		void renderText(font* f, std::wstring str, rect bound, col color, rect* tightBound); // tightBound can be 0; if it is 0, nothing renders

	public:
		size_t getNumFonts(void);
		void getFontInfo(size_t i, fontInfo* f);
		size_t getDefaultFont(void);
		font loadFont(size_t i, float pointSize);
		void deloadFont(font* f);
	};
}