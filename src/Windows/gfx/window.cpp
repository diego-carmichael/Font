// This file's a bit large, but I can't think of a
// reasonable way to split it up, and either way,
// it doesn't REALLY need to be that maintainable.
// (Famous Last Words)
#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "Windows/gfx/window.hpp"

#include "gfx/surface.hpp"
#include "dbg/log.hpp"
#include "windows/gfx/input.hpp"

#include <cmath>

namespace osw32 {
	// Map for identifying windows based on hwnd
	std::vector<window*> winmap {};
	void addWinmap(window* win) {
		winmap.push_back(win);
	}
	void remWinmap(window* win) {
		for (size_t w = 0; w < winmap.size(); ++w) {
			if (winmap[w] == win) {
				winmap.erase(winmap.begin() + w);
				return;
			}
		}
		dbg::log("Unable to find window " + std::to_string((size_t)win) + " for removal\n");
	}
	window* findWinmap(HWND hwnd) {
		for (size_t w = 0; w < winmap.size(); ++w) {
			if (winmap[w]->hwnd == hwnd) {
				return winmap[w];
			}
		}
		return 0;
	}

	float adjustForDPI(window* win, float val) {
		return ceilf(val * (96.f / GetDpiForWindow(win->hwnd)));
	}

	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure
	// https://gitlab.winehq.org/wine/wine/-/wikis/Wine-Developer's-Guide/List-of-Windows-Messages
	LRESULT wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		window* win = findWinmap(hwnd);
		if (!win) {
			dbg::log("wndproc call with no associated hwnd (this is normal, but shouldn't occur frequently over time)\n");
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		switch (uMsg) {
			default: return DefWindowProc(hwnd, uMsg, wParam, lParam); break;

			// https://learn.microsoft.com/en-us/windows/win32/learnwin32/closing-the-window
			case WM_CLOSE: {
				dbg::log("Window closed via WM_CLOSE\n");
				win->active = false;
				termd2d(&win->ren);
				PostQuitMessage(0);
				DestroyWindow(win->hwnd);
			} break;

			case WM_SIZE: {
				resized2d(&win->ren, LOWORD(lParam), HIWORD(lParam), win->sf);
			} break;

			// https://learn.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart
			case WM_DISPLAYCHANGE: {
				InvalidateRect(win->hwnd, NULL, FALSE);
			} break;

			case WM_PAINT: {
				paintd2d(&win->ren, hwnd, { 1.f, 1.f, 1.f, 1.f }, win->sf);
				// https://learn.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart
				ValidateRect(hwnd, NULL);
			} break;

			case WM_COMMAND: {
				if (win->currentMenu.size() == 0) {
					dbg::log("WM_COMMAND with no current menu...? Weird!\n");
					break;
				}
				bool found = false;
				for (size_t m = 0; m < win->currentMenu.size(); ++m) {
					found = callMenuID(&win->currentMenu[m], LOWORD(wParam));
					if (found) {
						break;
					}
				}
				if (!found) {
					dbg::log("WM_COMMAND with unrecognized ID " + std::to_string(LOWORD(wParam)) + "? Weird!\n");
				}
			} break;

			case WM_KEYDOWN: {
				// (To avoid repeating by holding down)
				if (lParam & (1 << 30)) {
					break;
				}
				gfx::inp::keyboardKey key = vkKey(vkMapLRKeys(wParam, lParam));
				if (key != gfx::inp::keyboardUnknown) {
					win->sf->onKeyPress.call((void*)((size_t)key));
				}
			} break;
			case WM_KEYUP: {
				gfx::inp::keyboardKey key = vkKey(vkMapLRKeys(wParam, lParam));
				if (key != gfx::inp::keyboardUnknown) {
					win->sf->onKeyRelease.call((void*)((size_t)key));
				}
			} break;

			case WM_LBUTTONDOWN: {
				win->sf->onMousePress.call((void*)((size_t)gfx::inp::mouseLeft));
			} break;
			case WM_LBUTTONUP: {
				win->sf->onMouseRelease.call((void*)((size_t)gfx::inp::mouseLeft));
			} break;
			case WM_RBUTTONDOWN: {
				win->sf->onMousePress.call((void*)((size_t)gfx::inp::mouseRight));
			} break;
			case WM_RBUTTONUP: {
				win->sf->onMouseRelease.call((void*)((size_t)gfx::inp::mouseRight));
			} break;

			// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove
			case WM_MOUSEMOVE: {
				float pos[2] = {
					adjustForDPI(win, LOWORD(lParam)), adjustForDPI(win, (float)HIWORD(lParam))
				};
				win->sf->onCursorMove.call((void*)pos);
			} break;

			case WM_MOUSEWHEEL: {
				float scroll = ((float)GET_WHEEL_DELTA_WPARAM(wParam)) / 120.f;
				win->sf->onCursorScroll.call(&scroll);
			} break;
		}

		return 0;
	}
}

void gfx::surface::getDimensions(uint32_t* width, uint32_t* height) {
	osw32::window* win = (osw32::window*)this->data;
	RECT rc;
	GetClientRect(win->hwnd, &rc);
	*width = osw32::adjustForDPI(win, rc.right - rc.left);
	*height = osw32::adjustForDPI(win, rc.bottom - rc.top);
}

void gfx::surface::setName(std::string name) {
	osw32::window* win = (osw32::window*)this->data;
	SetWindowText(win->hwnd, name.c_str());
}

void gfx::surface::getMousePos(float* x, float* y) {
	osw32::window* win = (osw32::window*)this->data;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(win->hwnd, &p);
	if (x) {
		*x = osw32::adjustForDPI(win, p.x);
	}
	if (y) {
		*y = osw32::adjustForDPI(win, p.y);
	}
}

#endif