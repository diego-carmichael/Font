#include "create/canvas/grid/grid.hpp"

#include "create/logic/font.hpp"
#include "dbg/log.hpp"
#include "general/math.hpp"

#include <cmath>

namespace cr {
	namespace cv {
		namespace gr {
			grid::grid(gfx::surface* sf, gfx::rect coverage) {
				this->sf = sf;
				this->coverage = coverage;
			}

			grid::~grid(void) {

			}

			float scaleBegin = 7.f;
			float scaleEnd = 14.f;
			float maxAlpha = 0.5f;
			gfx::col lineCol = { 0.5f, 0.5f, 0.5f, 1.f };

			void grid::render(void) {
				if (fnt::currentFont.cv.scale < scaleBegin) {
					return;
				}
				lineCol.a = math::minf(
					fnt::currentFont.cv.scale - scaleBegin, scaleEnd
				);
				lineCol.a /= scaleEnd;
				lineCol.a *= maxAlpha;

				float tlX = this->coverage.x - (this->coverage.w / 2.f);
				float tlY = this->coverage.y - (this->coverage.h / 2.f);
				fnt::currentFont.cv.clientPosToCanvas(
					tlX, &tlX, tlY, &tlY, this->coverage
				);
				tlX = ceilf(tlX);
				tlY = ceilf(tlY);
				fnt::currentFont.cv.canvasPosToClient(
					tlX, &tlX, tlY, &tlY, this->coverage
				);

				float brX = this->coverage.x + (this->coverage.w / 2.f);
				float brY = this->coverage.y + (this->coverage.h / 2.f);
				fnt::currentFont.cv.clientPosToCanvas(
					brX, &brX, brY, &brY, this->coverage
				);
				brX = floorf(brX);
				brY = floorf(brY);
				fnt::currentFont.cv.canvasPosToClient(
					brX, &brX, brY, &brY, this->coverage
				);

				// Vertical strips (left to right)
				float x = tlX;
				size_t s = 0;
				while (x <= brX+0.001f) {
					x = tlX + (fnt::currentFont.cv.scale * s);
					this->sf->renderLine(
						{ x, this->coverage.y - (this->coverage.h / 2.f) },
						{ x, this->coverage.y + (this->coverage.h / 2.f) },
						lineCol
					);
					++s;
				}

				// Horizontal strips (top to bottom)
				float y = tlY;
				s = 0;
				while (y < brY+0.001f) {
					y = tlY + (fnt::currentFont.cv.scale * s);
					this->sf->renderLine(
						{ this->coverage.x - (this->coverage.w / 2.f), y },
						{ this->coverage.x + (this->coverage.w / 2.f), y },
						lineCol
					);
					++s;
				}
			}

			void grid::changeCoverage(gfx::rect coverage) {
				this->coverage = coverage;
			}
		}
	}
}