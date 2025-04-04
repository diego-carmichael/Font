#include "create/canvas/glyph/glyph.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"

namespace cr {
	namespace cv {
		namespace gl {
			glyph::glyph(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box) {
				this->sf = sf;
				this->coverage = coverage;
				this->box = box;
			}

			glyph::~glyph(void) {

			}

			void glyph::render(void) {
				// B
				fnt::glyph testGlyph {};
				testGlyph.contours = std::vector<fnt::contour>(3);
				testGlyph.contours[0].type = fnt::contourTypeTTF;
				testGlyph.contours[0].data.ttf.in = true;
				testGlyph.contours[0].data.ttf.points = std::vector<fnt::ttfPoint>(11);
					testGlyph.contours[0].data.ttf.points[0].x = 86;
					testGlyph.contours[0].data.ttf.points[0].y = 64;
					testGlyph.contours[0].data.ttf.points[0].on = true;
					testGlyph.contours[0].data.ttf.points[1].x = 120;
					testGlyph.contours[0].data.ttf.points[1].y = 64;
					testGlyph.contours[0].data.ttf.points[1].on = true;
					testGlyph.contours[0].data.ttf.points[2].x = 164;
					testGlyph.contours[0].data.ttf.points[2].y = 64;
					testGlyph.contours[0].data.ttf.points[2].on = false;
					testGlyph.contours[0].data.ttf.points[3].x = 164;
					testGlyph.contours[0].data.ttf.points[3].y = 94;
					testGlyph.contours[0].data.ttf.points[3].on = true;
					testGlyph.contours[0].data.ttf.points[4].x = 164;
					testGlyph.contours[0].data.ttf.points[4].y = 124;
					testGlyph.contours[0].data.ttf.points[4].on = false;
					testGlyph.contours[0].data.ttf.points[5].x = 144;
					testGlyph.contours[0].data.ttf.points[5].y = 124;
					testGlyph.contours[0].data.ttf.points[5].on = true;
					testGlyph.contours[0].data.ttf.points[6].x = 168;
					testGlyph.contours[0].data.ttf.points[6].y = 124;
					testGlyph.contours[0].data.ttf.points[6].on = false;
					testGlyph.contours[0].data.ttf.points[7].x = 168;
					testGlyph.contours[0].data.ttf.points[7].y = 154;
					testGlyph.contours[0].data.ttf.points[7].on = true;
					testGlyph.contours[0].data.ttf.points[8].x = 168;
					testGlyph.contours[0].data.ttf.points[8].y = 192;
					testGlyph.contours[0].data.ttf.points[8].on = false;
					testGlyph.contours[0].data.ttf.points[9].x = 120;
					testGlyph.contours[0].data.ttf.points[9].y = 192;
					testGlyph.contours[0].data.ttf.points[9].on = true;
					testGlyph.contours[0].data.ttf.points[10].x = 86;
					testGlyph.contours[0].data.ttf.points[10].y = 192;
					testGlyph.contours[0].data.ttf.points[10].on = true;
				testGlyph.contours[1].type = fnt::contourTypeTTF;
				testGlyph.contours[1].data.ttf.in = false;
				testGlyph.contours[1].data.ttf.points = std::vector<fnt::ttfPoint>(7);
					testGlyph.contours[1].data.ttf.points[0].x = 104;
					testGlyph.contours[1].data.ttf.points[0].y = 78;
					testGlyph.contours[1].data.ttf.points[0].on = true;
					testGlyph.contours[1].data.ttf.points[1].x = 120;
					testGlyph.contours[1].data.ttf.points[1].y = 78;
					testGlyph.contours[1].data.ttf.points[1].on = true;
					testGlyph.contours[1].data.ttf.points[2].x = 146;
					testGlyph.contours[1].data.ttf.points[2].y = 78;
					testGlyph.contours[1].data.ttf.points[2].on = false;
					testGlyph.contours[1].data.ttf.points[3].x = 146;
					testGlyph.contours[1].data.ttf.points[3].y = 96;
					testGlyph.contours[1].data.ttf.points[3].on = true;
					testGlyph.contours[1].data.ttf.points[4].x = 146;
					testGlyph.contours[1].data.ttf.points[4].y = 118;
					testGlyph.contours[1].data.ttf.points[4].on = false;
					testGlyph.contours[1].data.ttf.points[5].x = 120;
					testGlyph.contours[1].data.ttf.points[5].y = 118;
					testGlyph.contours[1].data.ttf.points[5].on = true;
					testGlyph.contours[1].data.ttf.points[6].x = 104;
					testGlyph.contours[1].data.ttf.points[6].y = 118;
					testGlyph.contours[1].data.ttf.points[6].on = true;
				testGlyph.contours[2].type = fnt::contourTypeTTF;
				testGlyph.contours[2].data.ttf.in = false;
				testGlyph.contours[2].data.ttf.points = std::vector<fnt::ttfPoint>(7);
					testGlyph.contours[2].data.ttf.points[0].x = 104;
					testGlyph.contours[2].data.ttf.points[0].y = 132;
					testGlyph.contours[2].data.ttf.points[0].on = true;
					testGlyph.contours[2].data.ttf.points[1].x = 120;
					testGlyph.contours[2].data.ttf.points[1].y = 132;
					testGlyph.contours[2].data.ttf.points[1].on = true;
					testGlyph.contours[2].data.ttf.points[2].x = 150;
					testGlyph.contours[2].data.ttf.points[2].y = 132;
					testGlyph.contours[2].data.ttf.points[2].on = false;
					testGlyph.contours[2].data.ttf.points[3].x = 150;
					testGlyph.contours[2].data.ttf.points[3].y = 154;
					testGlyph.contours[2].data.ttf.points[3].on = true;
					testGlyph.contours[2].data.ttf.points[4].x = 150;
					testGlyph.contours[2].data.ttf.points[4].y = 176;
					testGlyph.contours[2].data.ttf.points[4].on = false;
					testGlyph.contours[2].data.ttf.points[5].x = 120;
					testGlyph.contours[2].data.ttf.points[5].y = 176;
					testGlyph.contours[2].data.ttf.points[5].on = true;
					testGlyph.contours[2].data.ttf.points[6].x = 104;
					testGlyph.contours[2].data.ttf.points[6].y = 176;
					testGlyph.contours[2].data.ttf.points[6].on = true;

				gfx::shape s;
				fnt::currentFont.glyphToShape(&testGlyph, &s, this->coverage);
				this->sf->renderShape(&s);
			}

			void glyph::changeCoverage(gfx::rect newCoverage) {
				this->coverage = newCoverage;
			}
		}
	}
}