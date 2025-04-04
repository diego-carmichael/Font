#pragma once

#include <cstdint>

namespace gfx {
	namespace inp {
		typedef uint16_t keyboardKey;
		const keyboardKey keyboardUnknown = 0;
		const keyboardKey keyboardLCtrl = 1;
		const keyboardKey keyboardRCtrl = 2;
		const keyboardKey keyboardLShift = 3;
		const keyboardKey keyboardRShift = 4;

		typedef uint16_t mouseButton;
		const mouseButton mouseUnknown = 0;
		const mouseButton mouseLeft = 1;
		const mouseButton mouseRight = 2;
	}
}