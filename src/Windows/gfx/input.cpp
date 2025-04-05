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
			case VK_LSHIFT: return gfx::inp::keyboardLShift; break;
			case VK_RSHIFT: return gfx::inp::keyboardRShift; break;
			case 0x41: return gfx::inp::keyboardA; break;
			case 0x42: return gfx::inp::keyboardB; break;
			case 0x43: return gfx::inp::keyboardC; break;
			case 0x44: return gfx::inp::keyboardD; break;
			case 0x45: return gfx::inp::keyboardE; break;
			case 0x46: return gfx::inp::keyboardF; break;
			case 0x47: return gfx::inp::keyboardG; break;
			case 0x48: return gfx::inp::keyboardH; break;
			case 0x49: return gfx::inp::keyboardI; break;
			case 0x4A: return gfx::inp::keyboardJ; break;
			case 0x4B: return gfx::inp::keyboardK; break;
			case 0x4C: return gfx::inp::keyboardL; break;
			case 0x4D: return gfx::inp::keyboardM; break;
			case 0x4E: return gfx::inp::keyboardN; break;
			case 0x4F: return gfx::inp::keyboardO; break;
			case 0x50: return gfx::inp::keyboardP; break;
			case 0x51: return gfx::inp::keyboardQ; break;
			case 0x52: return gfx::inp::keyboardR; break;
			case 0x53: return gfx::inp::keyboardS; break;
			case 0x54: return gfx::inp::keyboardT; break;
			case 0x55: return gfx::inp::keyboardU; break;
			case 0x56: return gfx::inp::keyboardV; break;
			case 0x57: return gfx::inp::keyboardW; break;
			case 0x58: return gfx::inp::keyboardX; break;
			case 0x59: return gfx::inp::keyboardY; break;
			case 0x5A: return gfx::inp::keyboardZ; break;
		}
	}

	WPARAM getVkKey(gfx::inp::keyboardKey key) {
		switch (key) {
			default: return 0; break;
			case gfx::inp::keyboardLCtrl: return VK_LCONTROL; break;
			case gfx::inp::keyboardRCtrl: return VK_RCONTROL; break;
			case gfx::inp::keyboardLShift: return VK_LSHIFT; break;
			case gfx::inp::keyboardRShift: return VK_RSHIFT; break;
			case gfx::inp::keyboardA: return 0x41; break;
			case gfx::inp::keyboardB: return 0x42; break;
			case gfx::inp::keyboardC: return 0x43; break;
			case gfx::inp::keyboardD: return 0x44; break;
			case gfx::inp::keyboardE: return 0x45; break;
			case gfx::inp::keyboardF: return 0x46; break;
			case gfx::inp::keyboardG: return 0x47; break;
			case gfx::inp::keyboardH: return 0x48; break;
			case gfx::inp::keyboardI: return 0x49; break;
			case gfx::inp::keyboardJ: return 0x4A; break;
			case gfx::inp::keyboardK: return 0x4B; break;
			case gfx::inp::keyboardL: return 0x4C; break;
			case gfx::inp::keyboardM: return 0x4D; break;
			case gfx::inp::keyboardN: return 0x4E; break;
			case gfx::inp::keyboardO: return 0x4F; break;
			case gfx::inp::keyboardP: return 0x50; break;
			case gfx::inp::keyboardQ: return 0x51; break;
			case gfx::inp::keyboardR: return 0x52; break;
			case gfx::inp::keyboardS: return 0x53; break;
			case gfx::inp::keyboardT: return 0x54; break;
			case gfx::inp::keyboardU: return 0x55; break;
			case gfx::inp::keyboardV: return 0x56; break;
			case gfx::inp::keyboardW: return 0x57; break;
			case gfx::inp::keyboardX: return 0x58; break;
			case gfx::inp::keyboardY: return 0x59; break;
			case gfx::inp::keyboardZ: return 0x5A; break;
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