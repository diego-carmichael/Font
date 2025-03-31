#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "Windows/gfx/input.hpp"

#include "gfx/surface.hpp"
#include "Windows/gfx/window.hpp"

namespace osw32 {
	// https://stackoverflow.com/a/5681468
	WPARAM vkMapLRKeys(WPARAM wParam, LPARAM lParam) {
		UINT scancode = (lParam & 0x00ff0000) >> 16;
		int extended  = (lParam & 0x01000000) != 0;
		switch (wParam) {
			default: return wParam; break;
			case VK_SHIFT: return MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX); break;
			case VK_CONTROL: return extended ? VK_RCONTROL : VK_LCONTROL; break;
			case VK_MENU: return extended ? VK_RMENU : VK_LMENU; break;
		}
	}

	// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	gfx::inp::keyboardKey vkKey(WPARAM key) {
		switch (key) {
			default: return gfx::inp::keyboardUnknown; break;
			case VK_LCONTROL: return gfx::inp::keyboardLCtrl; break;
			case VK_RCONTROL: return gfx::inp::keyboardRCtrl; break;
		}
	}

	WPARAM getVkKey(gfx::inp::keyboardKey key) {
		switch (key) {
			default: return 0; break;
			case gfx::inp::keyboardLCtrl: return VK_LCONTROL; break;
			case gfx::inp::keyboardRCtrl: return VK_RCONTROL; break;
		}
	}
}

namespace gfx {
	bool surface::isKeyDown(gfx::inp::keyboardKey key) {
		osw32::window* win = (osw32::window*)this->data;
		if (GetActiveWindow() != win->hwnd) {
			return false;
		}

		// https://stackoverflow.com/a/8640264
		WPARAM vkKey = osw32::getVkKey(key);
		if (!vkKey) {
			return false;
		}
		return (GetAsyncKeyState(vkKey) & (1 << 15));
	}
}

#endif