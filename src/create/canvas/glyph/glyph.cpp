#include "create/canvas/glyph/glyph.hpp"

#include "dbg/log.hpp"

#include <cmath>

namespace cr {
	namespace cv {
		namespace gl {
			glyph::glyph(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box) {
				this->sf = sf;
				this->coverage = coverage;
				this->box = box;
				this->pointBigRadius = 7.f;

				this->mousePressListener = sf->onMousePress.addListener(
					(void*)this, mousePress
				);
				this->mouseReleaseListener = sf->onMouseRelease.addListener(
					(void*)this, mouseRelease
				);
				this->cursorMoveListener = sf->onCursorMove.addListener(
					(void*)this, cursorMove
				);
			}

			glyph::~glyph(void) {
				this->sf->onCursorMove.removeListener(this->cursorMoveListener);
				this->sf->onMouseRelease.removeListener(this->mouseReleaseListener);
				this->sf->onMousePress.removeListener(this->mousePressListener);
			}

			void glyph::changeCoverage(gfx::rect newCoverage) {
				this->coverage = newCoverage;
			}
		}
	}
}