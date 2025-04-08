#pragma once

#include <cstdint>
#include <string>

namespace cr {
	/*typedef uint8_t action;
	const action actionUnknown = 0;

	typedef uint8_t actionSet;
	const actionSet actionSetUnknown = 0;

	std::string actionStr(actionSet set, action ac);

	typedef struct actionDesc actionDesc;
	struct actionDesc {
		action ac;
		actionSet set;
	};

	// Idle is always 0
	// canvasMoving is always 2

	const actionSet actionSetCanvas = 1;
	const action actionCanvasIdle = 0;
	const action actionCanvasResizing = 1;
	const action actionCanvasMoving = 2;

	const actionSet actionSetEdit = 2;
	const action actionEditIdle = 0;
	const action actionEditMoving = 2;
	const action actionEditMovingPoints = 3;*/

	typedef uint8_t actionSet;
	const actionSet actionSetUnknown = 0;

	typedef uint8_t action;
	const action actionUnknown = 0;

	const actionSet actionSetCanvas = 1;
	const action actionCanvasIdle = 0;
	const action actionCanvasMoving = 1;
	const action actionCanvasResizing = 2;
	typedef struct actionSetCanvasData actionSetCanvasData;
	struct actionSetCanvasData {
		int filler;
	};

	const actionSet actionSetGlyph = 2;
	const action actionGlyphIdle = 0;
	const action actionGlyphMoving = 1;
	const action actionGlyphMovingPoint = 2;
	typedef struct actionSetGlyphData actionSetGlyphData;
	struct actionSetGlyphData {
		bool selected;
	};

	typedef union actionData actionData;
	union actionData {
		actionSetCanvasData cv;
		actionSetGlyphData gl;
	};

	typedef struct actionState actionState;
	struct actionState {
		actionSet set;
		action ac;
		actionData data;
		bool idle;
	};

	std::string actionStr(actionState state);
}