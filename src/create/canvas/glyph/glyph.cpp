// This file's a bit obnoxiously large
// It's okay I think
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
						this->sf->renderDashedLine({ px, py, pnx, pny, 5.f }, { .50f, .50f, .50f, .50f });
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
						this->sf->renderCircle({ px, py, 4.75f }, { .00f, .58f, 1.0f, 1.f });
					} else {
						this->sf->renderCircle({ px, py, radiu }, { .25f, .25f, .25f, 1.f });
						this->sf->renderCircle({ px, py, 4.75f }, { .50f, .50f, .50f, 1.f });
					}
				}
			}

			void glyph::renderPoints(fnt::glyph* g) {
				if (fnt::currentFont.actionSet != cr::actionSetEdit) {
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

			void glyph::changeCoverage(gfx::rect newCoverage) {
				this->coverage = newCoverage;
			}

			void glyph::clickPointsContourTTF(fnt::ttfContour* c, float mx, float my, bool shift) {
				for (size_t p = 0; p < c->points.size(); ++p) {
					float px = c->points[p].x, py = c->points[p].y;
					px -= fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
					py -= fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
					fnt::currentFont.cv.canvasPosToClient(px, &px, py, &py, this->coverage);

					bool hover = (mx-px)*(mx-px) + (my-py)*(my-py) <= this->pointBigRadius*this->pointBigRadius;
					if (!hover) {
						if (!shift && c->points[p].selected) {
							c->points[p].selected = false;
						}
					} else {
						if (!c->points[p].selected) {
							c->points[p].selected = true;
						}
					}
				}
			}

			void glyph::movePointsContourTTF(fnt::ttfContour* c, float mx, float my, hst::pointMoveData* data) {
				for (size_t p = 0; p < c->points.size(); ++p) {
					if (!c->points[p].selected) {
						continue;
					}

					if (
						((float)c->points[p].x) + mx <= ((float)fnt::currentFont.cv.data.unscaledDim[0]) &&
						((float)c->points[p].x) + mx >= 0.f
					) {
						c->points[p].x += mx;
					}
					if (
						((float)c->points[p].y) + my <= ((float)fnt::currentFont.cv.data.unscaledDim[1]) &&
						((float)c->points[p].y) + my >= 0.f
					) {
						c->points[p].y += my;
					}

					if (data) {
						data->pointsMoved += 1;
						if (data->pointsMoved == 1) {
							data->newPos[0] = c->points[p].x;
							data->newPos[1] = c->points[p].y;
							data->prevPos[0] = data->newPos[0] - data->offset[0];
							data->prevPos[1] = data->newPos[1] - data->offset[1];
						}
					}
				}
			}

			void glyph::clickPoints(fnt::glyph* g, float mx, float my, bool shift) {
				for (size_t c = 0; c < g->contours.size(); ++c) {
					switch (g->contours[c].type) {
						default: dbg::log("Unrecognized click glyph contour type! Weird!\n"); break;

						case fnt::contourTypeTTF: {
							this->clickPointsContourTTF(&g->contours[c].data.ttf, mx, my, shift);
						} break;
					}
				}
			}

			void glyph::movePoints(fnt::glyph* g, float mx, float my, hst::pointMoveData* data) {
				for (size_t c = 0; c < g->contours.size(); ++c) {
					switch (g->contours[c].type) {
						default: dbg::log("Unrecognized move points contour type! Weird!\n"); break;

						case fnt::contourTypeTTF: {
							this->movePointsContourTTF(&g->contours[c].data.ttf, mx, my, data);
						} break;
					}
				}
			}

			void mousePress(ev::listener* l, void* data) {
				glyph* g = (glyph*)l->data;
				if (static_cast<gfx::inp::mouseButton>((size_t)data) != gfx::inp::mouseLeft) {
					return;
				}
				if (fnt::currentFont.actionSet != cr::actionSetEdit || fnt::currentFont.action != 0) {
					return;
				}

				float mx, my;
				g->sf->getMousePos(&mx, &my);
				g->clickPoints(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph],
					mx, my, g->sf->isKeyDown(gfx::inp::keyboardLShift)
				);
				g->sf->flagRender();

				if (!anyPointsSelected(&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph])) {
					return;
				}
				g->prevFont = fnt::currentFont.data;
				g->prevCanvas = fnt::currentFont.cv.data;
				fnt::currentFont.changeAction(
					cr::actionSetEdit, cr::actionEditMovingPoints
				);

				g->lastCursorPos[0] = mx;
				g->lastCursorPos[1] = my;
				fnt::currentFont.cv.clientPosToCanvas(
					g->lastCursorPos[0], &g->lastCursorPos[0],
					g->lastCursorPos[1], &g->lastCursorPos[1],
					g->coverage
				);
				g->lastCursorPos[0] += fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
				g->lastCursorPos[1] += fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
				g->lastCursorPos[0] = g->initCursorPos[0] = roundf(g->lastCursorPos[0]);
				g->lastCursorPos[1] = g->initCursorPos[1] = roundf(g->lastCursorPos[1]);
			}

			void mouseRelease(ev::listener* l, void* data) {
				glyph* g = (glyph*)l->data;
				if (static_cast<gfx::inp::mouseButton>((size_t)data) != gfx::inp::mouseLeft) {
					return;
				}
				if (fnt::currentFont.actionSet != cr::actionSetEdit ||
					fnt::currentFont.action != cr::actionEditMovingPoints
				) {
					return;
				}

				float pos[2];
				g->sf->getMousePos(&pos[0], &pos[1]);
				fnt::currentFont.cv.clientPosToCanvas(
					pos[0], &pos[0], pos[1], &pos[1], g->coverage
				);
				pos[0] += fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
				pos[1] += fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
				pos[0] = roundf(pos[0]);
				pos[1] = roundf(pos[1]);

				hst::event ev {};
				ev.type = hst::eventPointsMove;
				ev.data.pointMove.offset[0] = pos[0] - g->initCursorPos[0];
				ev.data.pointMove.offset[1] = pos[1] - g->initCursorPos[1];
				if (ev.data.pointMove.offset[0] != 0 || ev.data.pointMove.offset[1] != 0) {
					g->movePoints(
						&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph],
						pos[0] - g->lastCursorPos[0], pos[1] - g->lastCursorPos[1],
						&ev.data.pointMove
					);
					ev.prevFont = g->prevFont;
					ev.prevCanvas = g->prevCanvas;
					ev.newFont = fnt::currentFont.data;
					ev.newCanvas = fnt::currentFont.cv.data;
					cr::hst::addEvent(&ev);
				}

				g->sf->flagRender();
				fnt::currentFont.changeAction(
					cr::actionSetEdit, 0
				);
			}

			void cursorMove(ev::listener* l, void* data) {
				glyph* g = (glyph*)l->data;
				if (fnt::currentFont.actionSet != cr::actionSetEdit ||
					fnt::currentFont.action != cr::actionEditMovingPoints
				) {
					return;
				}

				float* (pos) = (float*)data;
				fnt::currentFont.cv.clientPosToCanvas(
					pos[0], &pos[0], pos[1], &pos[1], g->coverage
				);
				pos[0] += fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
				pos[1] += fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
				pos[0] = roundf(pos[0]);
				pos[1] = roundf(pos[1]);
				g->movePoints(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph],
					pos[0] - g->lastCursorPos[0], pos[1] - g->lastCursorPos[1], 0
				);

				g->lastCursorPos[0] = pos[0];
				g->lastCursorPos[1] = pos[1];
				g->sf->flagRender();
			}
		}
	}
}