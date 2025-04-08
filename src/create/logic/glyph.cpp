#include "create/logic/glyph.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"
#include "general/bytes.hpp"

namespace fnt {
	bool isGlyphTTFContourClockwise(ttfContour* ttf) {
		float sum = 0.f;
		for (size_t p = 0; p < ttf->points.size(); ++p) {
			size_t next = (p == ttf->points.size()-1) ?(0) :(p+1);
			sum += 
				(ttf->points[next].x - ttf->points[p].x) *
				(ttf->points[next].y + ttf->points[p].y)
			;
		}
		return sum >= 0.f;
	}

	void glyphTTFContourToShape(font* f, ttfContour* ttf, gfx::contour* c, gfx::rect coverage) {
		if (ttf->points.size() == 0) {
			dbg::log("Size 0 point contour! Weird!\n");
			return;
		}

		c->close = true;
		c->paths = std::vector<gfx::path>(0);

		bool shouldFlip = isGlyphTTFContourClockwise(ttf);
		if (shouldFlip) {
			shouldFlip = ttf->in;
		} else {
			shouldFlip = !ttf->in;
		}

		/* Code follows this logic:
			If current point is on:
				If no paths have been added yet:
					Set initial point as current point.
				If paths have been added:
					Add as line path.
			If current point is off:
				If no paths have been added yet:
					If previous point is on:
						Initial point is previous point.
					If previous point is off:
						Initial point is midpoint between previous point and current point.
				Add as quad Bezier.
				Control point is current point.
				If next point is on:
					End point is next point.
					Increment past next point for next loop.
				If next point is off:
					End point is midpoint between current point and next point.
		*/

		for (size_t pa = 0; pa < ttf->points.size(); ++pa) {
			size_t p = (shouldFlip) ?((ttf->points.size()-pa)-1) :(pa);
			if (ttf->points[p].on) {
				if (pa == 0) {
					c->initialX = ((float)ttf->points[p].x) - (f->cv.data.unscaledDim[0] / 2.f);
					c->initialY = ((float)ttf->points[p].y) - (f->cv.data.unscaledDim[1] / 2.f);
					f->cv.canvasPosToClient(
						c->initialX, &c->initialX, c->initialY, &c->initialY, coverage
					);
				} else {
					gfx::path path;
					path.type = gfx::pathTypeLine;

					path.data.line.x = ((float)ttf->points[p].x) - (f->cv.data.unscaledDim[0] / 2.f);
					path.data.line.y = ((float)ttf->points[p].y) - (f->cv.data.unscaledDim[1] / 2.f);
					f->cv.canvasPosToClient(
						path.data.line.x, &path.data.line.x,
						path.data.line.y, &path.data.line.y, coverage
					);

					c->paths.push_back(path);
				}
			}
			else {
				if (pa == 0) {
					size_t prevP;
					if (!shouldFlip) {
						prevP = (p == 0) ?(ttf->points.size()-1) :(p-1);
					} else {
						prevP = (p == ttf->points.size()-1) ?(0) :(p+1);
					}
					if (ttf->points[prevP].on) {
						c->initialX = ((float)ttf->points[prevP].x) - (f->cv.data.unscaledDim[0] / 2.f);
						c->initialY = ((float)ttf->points[prevP].y) - (f->cv.data.unscaledDim[1] / 2.f);
						f->cv.canvasPosToClient(
							c->initialX, &c->initialX, c->initialY, &c->initialY, coverage
						);
					} else {
						c->initialX = (((float)ttf->points[prevP].x) + ((float)ttf->points[p].x)) / 2.f;
						c->initialY = (((float)ttf->points[prevP].y) + ((float)ttf->points[p].y)) / 2.f;
						c->initialX -= f->cv.data.unscaledDim[0] / 2.f;
						c->initialY -= f->cv.data.unscaledDim[1] / 2.f;
						f->cv.canvasPosToClient(
							c->initialX, &c->initialX, c->initialY, &c->initialY, coverage
						);
					}
				}
				gfx::path path;
				path.type = gfx::pathTypeQuadBezier;

				path.data.quadBezier.ctrlX = ((float)ttf->points[p].x) - (f->cv.data.unscaledDim[0] / 2.f);
				path.data.quadBezier.ctrlY = ((float)ttf->points[p].y) - (f->cv.data.unscaledDim[1] / 2.f);
				f->cv.canvasPosToClient(
					path.data.quadBezier.ctrlX, &path.data.quadBezier.ctrlX,
					path.data.quadBezier.ctrlY, &path.data.quadBezier.ctrlY, coverage
				);

				size_t nextP;
				if (!shouldFlip) {
					nextP = (p == ttf->points.size()-1) ?(0) :(p+1);
				} else {
					nextP = (p == 0) ?(ttf->points.size()-1) :(p-1);
				}
				if (ttf->points[nextP].on) {
					path.data.quadBezier.endX = ((float)ttf->points[nextP].x) - (f->cv.data.unscaledDim[0] / 2.f);
					path.data.quadBezier.endY = ((float)ttf->points[nextP].y) - (f->cv.data.unscaledDim[1] / 2.f);
					f->cv.canvasPosToClient(
						path.data.quadBezier.endX, &path.data.quadBezier.endX,
						path.data.quadBezier.endY, &path.data.quadBezier.endY, coverage
					);
					p += 1;
				}
				else {
					path.data.quadBezier.endX = (((float)ttf->points[nextP].x) + ((float)ttf->points[p].x)) / 2.f;
					path.data.quadBezier.endY = (((float)ttf->points[nextP].y) + ((float)ttf->points[p].y)) / 2.f;
					path.data.quadBezier.endX -= f->cv.data.unscaledDim[0] / 2.f;
					path.data.quadBezier.endY -= f->cv.data.unscaledDim[1] / 2.f;
					f->cv.canvasPosToClient(
						path.data.quadBezier.endX, &path.data.quadBezier.endX,
						path.data.quadBezier.endY, &path.data.quadBezier.endY, coverage
					);
				}

				c->paths.push_back(path);
			}
		}
	}

	void font::glyphToShape(glyph* g, gfx::shape* s, gfx::rect coverage) {
		s->shapeColor = { 0.f, 0.f, 0.f, 1.f };
		s->borderThickness = 0.f;
		s->contours = std::vector<gfx::contour>(g->contours.size());

		for (size_t c = 0; c < g->contours.size(); ++c) {
			switch (g->contours[c].type) {
				default: dbg::log("Unrecognized glyph contour type! Weird!\n"); break;

				case contourTypeTTF: {
					glyphTTFContourToShape(
						this, &g->contours[c].data.ttf, &s->contours[c], coverage
					);
				} break;
			}
		}
	}

	bool anyPointsSelected(glyph* g) {
		for (size_t c = 0; c < g->contours.size(); ++c) {
			switch (g->contours[c].type) {
				default: dbg::log("Unrecognized point selected contour type! Weird!\n"); break;

				case contourTypeTTF: {
					for (size_t p = 0; p < g->contours[c].data.ttf.points.size(); ++p) {
						if (g->contours[c].data.ttf.points[p].selected) {
							return true;
						}
					}
				} break;
			}
		}
		return false;
	}

	yak::chunk writeContourTTF(ttfContour* ttf) {
		// cttf...1
		yak::chunk c = {};
		c.id = 0x637474662E2E2E31;
		c.data = std::vector<uint8_t>(1 + (ttf->points.size() * 5));
		c.data[0] = (ttf->in) ?(1) :(0);

		for (size_t p = 0; p < ttf->points.size(); ++p) {
			size_t i = 1 + (p * 5);
			byte::be::writeu16(c.data.data()+i,   ttf->points[p].x);
			byte::be::writeu16(c.data.data()+i+2, ttf->points[p].y);
			c.data[i+4] = (ttf->points[p].on) ?(1) :(0);
		}

		return c;
	}

	int readContourTTF(ttfContour* ttf, yak::chunk* ck, uint16_t dim[2]) {
		if (ck->data.size() == 0 || ((ck->data.size() - 1) % 5) != 0) {
			dbg::log("Size of cttf...1 chunk invalid\n");
			return -1;
		}
		ttf->in = (ck->data[0] == 0) ?(false) :(true);
		ttf->points = std::vector<ttfPoint>((ck->data.size() - 1) / 5);

		for (size_t p = 0; p < ttf->points.size(); ++p) {
			size_t i = 1 + (p * 5);
			ttf->points[p].x = byte::be::readu16(ck->data.data() + i);
			ttf->points[p].y = byte::be::readu16(ck->data.data() + i + 2);
			ttf->points[p].on = (ck->data[i + 4] == 0) ?(false) :(true);
			ttf->points[p].selected = false;

			if (ttf->points[p].x > dim[0] || ttf->points[p].y > dim[1]) {
				dbg::log("Point within cttf...1 out of range\n");
				return -1;
			}
		}

		return 0;
	}

	yak::chunk writeGlyph(glyph* g) {
		// glyf...1
		yak::chunk c = {};
		c.id = 0x676C79662E2E2E31;
		c.data = std::vector<uint8_t>(4);
		byte::be::writeu32(c.data.data(), g->codepoint);

		for (size_t ic = 0; ic < g->contours.size(); ++ic) {
			switch (g->contours[ic].type) {
				default: {
					dbg::log("Unrecognized contour type when writing glyph! Weird!\n");
				} break;

				case contourTypeTTF: {
					c.children.push_back(writeContourTTF(&g->contours[ic].data.ttf));
				} break;
			}
		}

		return c;
	}

	int readGlyph(glyph* g, yak::chunk* ck, uint16_t dim[2]) {
		if (ck->data.size() != 4) {
			dbg::log("Invalid glyf...1 chunk size\n");
			return -1;
		}
		g->codepoint = byte::be::readu32(ck->data.data());
		g->contours = std::vector<contour>(0);

		for (size_t ic = 0; ic < ck->children.size(); ++ic) {
			switch (ck->children[ic].id) {
				default: break;

				// cttf...1
				case 0x637474662E2E2E31: {
					contour c = {};
					c.type = contourTypeTTF;
					if (readContourTTF(&c.data.ttf, &ck->children[ic], dim) != 0) {
						return -1;
					}
					g->contours.push_back(c);
				} break;
			}
		}

		return 0;
	}
}