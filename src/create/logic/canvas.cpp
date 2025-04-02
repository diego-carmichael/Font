#include "create/logic/canvas.hpp"

namespace fnt {
	canvas::canvas(void) {
		this->unscaled.x = 0;
		this->unscaled.y = 0;
		this->unscaled.w = 256;
		this->unscaled.h = 256;
		this->scale = 1;

		this->ascender = 64.f;
		this->descender = 128.f;
		this->lineGap = 40.f;
	}

	gfx::rect canvas::getUnscaled(gfx::rect coverage) {
		return {
			coverage.x + this->unscaled.x,
			coverage.y + this->unscaled.y,
			this->unscaled.w,
			this->unscaled.h
		};
	}

	gfx::rect canvas::getScaled(gfx::rect coverage) {
		float x, y;
		this->canvasPosToClient(0.f, &x, 0.f, &y, coverage);
		return {
			x, y,
			this->unscaled.w * this->scale,
			this->unscaled.h * this->scale
		};
	}

	void canvas::canvasPosToClient(float ix, float* ox, float iy, float* oy, gfx::rect coverage) {
		if (ox) {
			//*ox = coverage.x + ((ix+this->unscaled.x) * this->scale);
			*ox = coverage.x + ((ix + this->unscaled.x) * this->scale);
		}
		if (oy) {
			//*oy = coverage.y + ((iy+this->unscaled.y) * this->scale);
			*oy = coverage.y + ((iy + this->unscaled.y) * this->scale);
		}
	}

	void canvas::clientPosToCanvas(float ix, float* ox, float iy, float* oy, gfx::rect coverage) {
		if (ox) {
			//*ox = (ix / this->scale) - coverage.x;
			//*ox = ((ix) / this->scale) - this->unscaled.x;
			*ox = ((ix - coverage.x) / this->scale) - this->unscaled.x;
		}
		if (oy) {
			//*oy = (iy / this->scale) - coverage.y;
			//*oy = ((iy) / this->scale) - this->unscaled.y;
			*oy = ((iy - coverage.y) / this->scale) - this->unscaled.y;
		}
	}

	void canvas::moveScaled(float diffX, float diffY) {
		this->unscaled.x += diffX / this->scale;
		this->unscaled.y += diffY / this->scale;
		this->onCanvasChange.call(0);
	}

	void canvas::rescaleAroundPoint(float newScale, gfx::rect coverage, float x, float y) {
		// Is this the best way of doing this? No.
		// Does it work? Yeah I think
		float cx, cy;
		this->clientPosToCanvas(x, &cx, y, &cy, coverage);
		this->unscaled.x -= cx + this->unscaled.x;
		this->unscaled.y -= cy + this->unscaled.y;
		this->scale = newScale;
		this->clientPosToCanvas(x, &cx, y, &cy, coverage);
		this->unscaled.x += cx + this->unscaled.x;
		this->unscaled.y += cy + this->unscaled.y;
		this->onCanvasChange.call(0);
	}
}