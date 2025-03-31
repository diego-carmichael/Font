#pragma once

#include "gfx/input.hpp"

#include <Windows.h>

namespace osw32 {
	WPARAM vkMapLRKeys(WPARAM wParam, LPARAM lParam);
	gfx::inp::keyboardKey vkKey(WPARAM key);
	WPARAM getVkKey(gfx::inp::keyboardKey key);
}