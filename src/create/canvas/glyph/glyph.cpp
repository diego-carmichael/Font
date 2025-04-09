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
				this->eventAddListener = cr::hst::onEventAdd.addListener(
					(void*)this, cr::cv::gl::event
				);
				this->eventUndoListener = cr::hst::onEventUndo.addListener(
					(void*)this, cr::cv::gl::event
				);
				this->eventRedoListener = cr::hst::onEventRedo.addListener(
					(void*)this, cr::cv::gl::event
				);
			}

			glyph::~glyph(void) {
				cr::hst::onEventRedo.removeListener(this->eventRedoListener);
				cr::hst::onEventUndo.removeListener(this->eventUndoListener);
				cr::hst::onEventAdd.removeListener(this->eventAddListener);
				this->sf->onCursorMove.removeListener(this->cursorMoveListener);
				this->sf->onMouseRelease.removeListener(this->mouseReleaseListener);
				this->sf->onMousePress.removeListener(this->mousePressListener);
			}

			void glyph::changeCoverage(gfx::rect newCoverage) {
				this->coverage = newCoverage;
			}

			void event(ev::listener* l, void* data) {
				if (fnt::currentFont.acState.set != cr::actionSetGlyph) {
					return;
				}
				fnt::currentFont.acState.data.gl.selected = fnt::anyPointsSelected(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph]
				);
			}
		}
	}
}