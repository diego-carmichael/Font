#pragma once

#include "gfx/defs.hpp"
#include "general/event.hpp"

namespace fnt {
	typedef struct canvasData canvasData;
	struct canvasData {
		float unscaledDim[2];
		float ascender; // Relative to top of canvas (moving down)
		float descender; // Relative to ascender (moving down)
		float lineGap; // Relative to ascender (moving up) / descender (moving down)
	};
	void defaultCanvasData(canvasData* data);

	class canvas {
	public:
		canvas(void);
		canvasData data;

	public:
		// Position relative to center of coverage
		float unscaledPos[2];
		float scale;

	public:
		// Non-relative to center of coverage (actually where it is)
		gfx::rect getUnscaled(gfx::rect coverage);
		gfx::rect getScaled(gfx::rect coverage);

		// Canvas == position relative to center of canvas by canvas coordiantes, ignoring scaling
		// Client == position relative to whole surface
		void canvasPosToClient(float ix, float* ox, float iy, float* oy, gfx::rect coverage);
		void clientPosToCanvas(float ix, float* ox, float iy, float* oy, gfx::rect coverage);
	public:
		// For when it:
		// * moves.
		ev::event onCanvasChange {}; // data = 0

		void moveScaled(float diffX, float diffY);
		// x and y are client
		void rescaleAroundPoint(float newScale, gfx::rect coverage, float x, float y);
	};
}