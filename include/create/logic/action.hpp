#pragma once

#include <cstdint>

namespace cr {
	typedef uint8_t action;
	const action actionUnknown = 0;

	typedef uint8_t actionSet;
	const actionSet actionSetUnknown = 0;

	const actionSet actionSetCanvas = 1;
	const action actionCanvasIdle = 0;
	const action actionCanvasResizing = 1;
	const action actionCanvasMoving = 2;

	const actionSet actionSetEdit = 2;
	const action actionEditIdle = 0;
}