#include "create/canvas/glyph/glyph.hpp"

#include "dbg/log.hpp"
#include <cmath>

namespace cr {
	namespace cv {
		namespace gl {
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
				if (fnt::currentFont.acState.set != cr::actionSetGlyph || !fnt::currentFont.acState.idle) {
					return;
				}

				float mx, my;
				g->sf->getMousePos(&mx, &my);
				g->clickPoints(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph],
					mx, my, g->sf->isKeyDown(gfx::inp::keyboardLShift)
				);
				fnt::currentFont.acState.data.gl.selected = fnt::anyPointsSelected(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph]
				);
				g->sf->flagRender();

				if (!fnt::currentFont.acState.data.gl.selected) {
					return;
				}
				g->prevFont = fnt::currentFont.data;
				g->prevCanvas = fnt::currentFont.cv.data;
				cr::actionState state = fnt::currentFont.acState;
				state.idle = false;
				state.ac = cr::actionGlyphMovingPoint;
				fnt::currentFont.changeAction(state);

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
				float pos[2];
				g->sf->getMousePos(&pos[0], &pos[1]);
				fnt::currentFont.cv.clientPosToCanvas(
					pos[0], &pos[0], pos[1], &pos[1], g->coverage
				);
				pos[0] += fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
				pos[1] += fnt::currentFont.cv.data.unscaledDim[1] / 2.f;
				pos[0] = roundf(pos[0]);
				pos[1] = roundf(pos[1]);

				if (static_cast<gfx::inp::mouseButton>((size_t)data) == gfx::inp::mouseRight) {
					g->lastCursorPos[0] = pos[0];
					g->lastCursorPos[1] = pos[1];
					return;
				}
				if (static_cast<gfx::inp::mouseButton>((size_t)data) != gfx::inp::mouseLeft) {
					return;
				}
				if (fnt::currentFont.acState.set != cr::actionSetGlyph) {
					return;
				}
				if (fnt::currentFont.acState.ac != cr::actionGlyphMovingPoint) {
					return;
				}

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
				cr::actionState state = fnt::currentFont.acState;
				state.idle = true;
				state.ac = 0;
				fnt::currentFont.changeAction(state);
			}

			void cursorMove(ev::listener* l, void* data) {
				glyph* g = (glyph*)l->data;
				if (fnt::currentFont.acState.set != cr::actionSetGlyph) {
					return;
				}
				if (fnt::currentFont.acState.ac != cr::actionGlyphMovingPoint) {
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