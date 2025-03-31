#pragma once

#include "gfx/surface.hpp"
#include "Windows/gfx/menu.hpp"
#include "Windows/gfx/d2d.hpp"

#include <Windows.h>
#include <vector>

namespace osw32 {
	typedef struct window window;
	struct window {
		bool active;
		HWND hwnd;
		d2d ren;
		gfx::surface* sf;
		std::vector<menu> currentMenu;
	};

	extern std::vector<window*> winmap;
	void addWinmap(window* win);
	void remWinmap(window* win);
	window* findWinmap(HWND hwnd);

	LRESULT wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
}