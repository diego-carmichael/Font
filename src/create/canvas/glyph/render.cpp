#include "create/canvas/glyph/glyph.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"

namespace cr {
	namespace cv {
		namespace gl {
			void glyph::renderContourTTF(fnt::ttfContour* c) {
				// (Must be rendered separately for order)

				// Lines
				for (size_t p = 0; p < c->points.size(); ++p) {
					float px = c->points[p].x, py = c->points[p].y;
					px -= fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
					py -= fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
					fnt::currentFont.cv.canvasPosToClient(px, &px, py, &py, this->coverage);

					size_t nextp = (p == c->points.size()-1) ?(0) :(p+1);
					float pnx = c->points[nextp].x, pny = c->points[nextp].y;
					pnx -= fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
					pny -= fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
					fnt::currentFont.cv.canvasPosToClient(pnx, &pnx, pny, &pny, this->coverage);
					if (c->points[p].selected || c->points[nextp].selected) {
						this->sf->renderLine({ px, py, pnx, pny, 5.f }, { .25f, .68f, 1.0f, .50f });
					} else {
						this->sf->renderDashedLine({ px, py, pnx, pny, 3.f }, { .50f, .50f, .50f, .50f });
					}
				}

				// Points
				for (size_t p = 0; p < c->points.size(); ++p) {
					float px = c->points[p].x, py = c->points[p].y;
					px -= fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
					py -= fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
					fnt::currentFont.cv.canvasPosToClient(px, &px, py, &py, this->coverage);
					float radiu = this->pointBigRadius;

					if (c->points[p].selected) {
						this->sf->renderCircle({ px, py, radiu }, { .50f, .79f, 1.0f, 1.f });
						if (c->points[p].on) {
							this->sf->renderCircle({ px, py, 4.75f }, { .00f, .58f, 1.0f, 1.f });
						} else {
							this->sf->renderCircle({ px, py, 4.75f }, { 1.0f, 1.0f, 1.0f, 1.f });
						}
					} else {
						this->sf->renderCircle({ px, py, radiu }, { .25f, .25f, .25f, 1.f });
						if (c->points[p].on) {
							this->sf->renderCircle({ px, py, 4.75f }, { .50f, .50f, .50f, 1.f });
						} else {
							this->sf->renderCircle({ px, py, 4.75f }, { 1.0f, 1.0f, 1.0f, 1.f });
						}
					}
				}
			}

			void glyph::renderPoints(fnt::glyph* g) {
				if (fnt::currentFont.acState.set != cr::actionSetGlyph) {
					return;
				}

				for (size_t c = 0; c < g->contours.size(); ++c) {
					switch (g->contours[c].type) {
						default: dbg::log("Unrecognized render glyph contour type! Weird!\n"); break;

						case fnt::contourTypeTTF: {
							this->renderContourTTF(&g->contours[c].data.ttf);
						} break;
					}
				}
			}

			void glyph::renderGlyph(void) {
				if (fnt::currentFont.data.glyphs.size() == 0 ||
					fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph].contours.size() == 0
				) {
				 	return;
				}

				gfx::shape s;
				fnt::currentFont.glyphToShape(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph],
					&s, this->coverage
				);
				this->sf->renderShape(&s);
				this->renderPoints(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph]
				);
			}
		}
	}
}