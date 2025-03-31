#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "Windows/gfx/menu.hpp"

#include "gfx/surface.hpp"
#include "Windows/gfx/window.hpp"

#include <cstdint>

namespace osw32 {
	menu processGfxMenu(gfx::menu* gfxMenu, UINT* pid, HMENU parentMenu) {
		menu mn {};
		mn.data = gfxMenu->data;
		mn.onClick = gfxMenu->onClick;
		mn.subMenus = std::vector<menu>(gfxMenu->subMenus.size());

		mn.hMenu = CreatePopupMenu();
		if (gfxMenu->subMenus.size() > 0) {
			AppendMenu(parentMenu, MF_STRING | MF_POPUP, static_cast<UINT>(reinterpret_cast<uintptr_t>(mn.hMenu)), gfxMenu->title.c_str());
			for (size_t m = 0; m < gfxMenu->subMenus.size(); ++m) {
				mn.subMenus[m] = processGfxMenu(&gfxMenu->subMenus[m], pid, mn.hMenu);
			}
		}
		else {
			*pid += 1;
			mn.id = *pid;
			AppendMenu(parentMenu, MF_STRING, mn.id, gfxMenu->title.c_str());
		}
		return mn;
	}

	bool callMenuID(menu* mn, UINT id) {
		if (mn->subMenus.size() == 0) {
			if (mn->id == id) {
				if (mn->onClick) {
					mn->onClick(mn->data);
				}
				return true;
			}
			return false;
		}
		for (size_t m = 0; m < mn->subMenus.size(); ++m) {
			if (callMenuID(&mn->subMenus[m], id)) {
				return true;
			}
		}
		return false;
	}
}

void gfx::surface::setMenu(std::vector<gfx::menu> mn) {
	osw32::window* win = (osw32::window*)this->data;
	win->currentMenu = std::vector<osw32::menu>(mn.size());

	HMENU hMenu = CreateMenu();
	UINT id = 9000;
	for (size_t m = 0; m < mn.size(); ++m) {
		win->currentMenu[m] = osw32::processGfxMenu(&mn[m], &id, hMenu);
	}
	SetMenu(win->hwnd, hMenu);
}

#endif