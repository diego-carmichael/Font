#pragma once

#include "gfx/menu.hpp"

#include <Windows.h>
#include <vector>

namespace osw32 {
	typedef struct menu menu;
	struct menu {
		UINT id;
		HMENU hMenu;
		gfx::menuType type;
		void* data;
		void (*onClick)(void*);
		std::vector<menu> subMenus;
	};

	menu processGfxMenu(gfx::menu* gfxMenu, UINT* pid, HMENU parentMenu);
	bool callMenuID(menu* mn, UINT id);
}