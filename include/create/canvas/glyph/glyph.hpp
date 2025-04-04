#pragma once

#include "gui/scene.hpp"
#include "create/infoBox/infoBox.hpp"
#include "create/logic/font.hpp"

namespace cr {
	namespace cv {
		namespace gl {
			class glyph : public gui::element {
			public:
				gfx::surface* sf;
				gfx::rect coverage;
				ib::infoBox* box;
				ev::listener* mousePressListener;
				ev::listener* mouseReleaseListener;
				ev::listener* cursorMoveListener;
				float pointBigRadius;
				float lastCursorPos[2];
			public:
				glyph(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box);
				~glyph(void);
			public:
				void renderContourTTF(fnt::ttfContour* c);
				void renderPoints(fnt::glyph* g);
				void renderGlyph(void);
				void changeCoverage(gfx::rect newCoverage);
			public:
				void clickPointsContourTTF(fnt::ttfContour* c, float mx, float my, bool shift);
				void movePointsContourTTF(fnt::ttfContour* c, float mx, float my);
				void clickPoints(fnt::glyph* g, float mx, float my, bool shift);
				void movePoints(fnt::glyph* g, float mx, float my);
			};

			void mousePress(ev::listener* l, void* data);
			void mouseRelease(ev::listener* l, void* data);
			void cursorMove(ev::listener* l, void* data);
		}
	}
}