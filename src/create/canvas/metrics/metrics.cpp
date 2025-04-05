#include "create/canvas/metrics/metrics.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"

namespace cr {
	namespace cv {
		namespace mt {
			metrics::metrics(gfx::surface* sf, gfx::rect coverage) {
				this->sf = sf;
				this->coverage = coverage;
			}

			metrics::~metrics(void) {

			}

			void metrics::render(void) {
				gfx::rect rect {};
				rect.x = 0.f;
				rect.w = fnt::currentFont.cv.data.unscaledDim[0] * fnt::currentFont.cv.scale;
				float h = fnt::currentFont.cv.data.unscaledDim[1];

				// Ascender
				rect.h = fnt::currentFont.cv.data.ascender * fnt::currentFont.cv.scale;
				rect.y = -(h / 2.f) + (fnt::currentFont.cv.data.ascender / 2.f);
				fnt::currentFont.cv.canvasPosToClient(
					rect.x, &rect.x, rect.y, &rect.y, this->coverage
				);
				this->sf->renderRect(rect, { .85f, .85f, .85f, 1.f });

				// Descender
				rect.h = h - fnt::currentFont.cv.data.ascender - fnt::currentFont.cv.data.descender;
				rect.y = (h / 2.f) - (rect.h / 2.f);
				rect.h *= fnt::currentFont.cv.scale;
				fnt::currentFont.cv.canvasPosToClient(0, 0, rect.y, &rect.y, this->coverage);
				this->sf->renderRect(rect, { .85f, .85f, .85f, 1.f });

				// Ascender line gap
				rect.h = fnt::currentFont.cv.data.ascender - fnt::currentFont.cv.data.lineGap;
				rect.y = -(h / 2.f) + (rect.h / 2.f);
				rect.h *= fnt::currentFont.cv.scale;
				fnt::currentFont.cv.canvasPosToClient(0, 0, rect.y, &rect.y, this->coverage);
				this->sf->renderRect(rect, { .55f, .55f, .55f, 1.f });

				// Descender line gap
				rect.h = 
					(h - fnt::currentFont.cv.data.ascender - fnt::currentFont.cv.data.descender)
					- fnt::currentFont.cv.data.lineGap
				;
				rect.y = (h / 2.f) - (rect.h / 2.f);
				rect.h *= fnt::currentFont.cv.scale;
				fnt::currentFont.cv.canvasPosToClient(0, 0, rect.y, &rect.y, this->coverage);
				this->sf->renderRect(rect, { .55f, .55f, .55f, 1.f });
			}

			void metrics::changeCoverage(gfx::rect coverage) {
				this->coverage = coverage;
			}
		}
	}
}