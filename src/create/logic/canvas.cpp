#include "create/logic/canvas.hpp"

namespace fnt {
	void defaultCanvasData(canvasData* data) {
		data->unscaledDim[0] = 256;
		data->unscaledDim[1] = 256;
		data->ascender = 64;
		data->descender = 128;
		data->lineGap = 40;
	}

	const float maxUnscaledDim[2] = { 1024.f, 1024.f };
	const float minUnscaledDim[2] = { 64.f, 64.f };

	bool validateMetrics(canvasData* data) {
		if (data->ascender == 0 || data->descender == 0 ||
			data->lineGap == 0) {
			return false;
		}
		if (data->ascender >= data->unscaledDim[1] ||
			data->ascender + data->descender >= data->unscaledDim[1]) {
			return false;
		}
		if (data->ascender - data->lineGap < 0.f ||
			data->descender + data->lineGap > data->unscaledDim[1]) {
			return false;
		}

		return true;
	}

	canvas::canvas(void) {
		defaultCanvasData(&this->data);
		this->unscaledPos[0] = 0;
		this->unscaledPos[1] = 0;
		this->scale = 1;
	}

	gfx::rect canvas::getUnscaled(gfx::rect coverage) {
		return {
			coverage.x + this->unscaledPos[0],
			coverage.y + this->unscaledPos[1],
			this->data.unscaledDim[0],
			this->data.unscaledDim[1]
		};
	}

	gfx::rect canvas::getScaled(gfx::rect coverage) {
		float x, y;
		this->canvasPosToClient(0.f, &x, 0.f, &y, coverage);
		return {
			x, y,
			this->data.unscaledDim[0] * this->scale,
			this->data.unscaledDim[1] * this->scale
		};
	}

	void canvas::canvasPosToClient(float ix, float* ox, float iy, float* oy, gfx::rect coverage) {
		if (ox) {
			*ox = coverage.x + ((ix + this->unscaledPos[0]) * this->scale);
		}
		if (oy) {
			*oy = coverage.y + ((iy + this->unscaledPos[1]) * this->scale);
		}
	}

	void canvas::clientPosToCanvas(float ix, float* ox, float iy, float* oy, gfx::rect coverage) {
		if (ox) {
			*ox = ((ix - coverage.x) / this->scale) - this->unscaledPos[0];
		}
		if (oy) {
			*oy = ((iy - coverage.y) / this->scale) - this->unscaledPos[1];
		}
	}

	void canvas::moveScaled(float diffX, float diffY) {
		this->unscaledPos[0] += diffX / this->scale;
		this->unscaledPos[1] += diffY / this->scale;
		this->onCanvasChange.call(0);
	}

	void canvas::rescaleAroundPoint(float newScale, gfx::rect coverage, float x, float y) {
		// Is this the best way of doing this? No.
		// Does it work? Yeah I think
		float cx, cy;
		this->clientPosToCanvas(x, &cx, y, &cy, coverage);
		this->unscaledPos[0] -= cx + this->unscaledPos[0];
		this->unscaledPos[1] -= cy + this->unscaledPos[1];
		this->scale = newScale;
		this->clientPosToCanvas(x, &cx, y, &cy, coverage);
		this->unscaledPos[0] += cx + this->unscaledPos[0];
		this->unscaledPos[1] += cy + this->unscaledPos[1];
		this->onCanvasChange.call(0);
	}
}