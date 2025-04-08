#include "create/canvas/glyph/glyph.hpp"

#include "dbg/log.hpp"
#include "create/create.hpp"
#include "general/math.hpp"
#include "create/logic/history.hpp"

#include <cmath>

namespace cr {
	namespace cv {
		namespace gl {
			void closestPointSelectTTF(fnt::ttfContour* ttf, float* smallestDist, size_t* op, float mx, float my) {
				for (size_t p = 0; p < ttf->points.size(); ++p) {
					size_t nextp = (p == ttf->points.size()-1) ?(0) :(p+1);
					if (!ttf->points[p].selected && !ttf->points[nextp].selected) {
						continue;
					}

					float ox, oy;
					math::closestPointOnLinef(
						ttf->points[p].x, ttf->points[p].y,
						ttf->points[nextp].x, ttf->points[nextp].y,
						mx, my, &ox, &oy
					);
					float dist = math::distf(ox, oy, mx, my);
					if (dist < *smallestDist) {
						dbg::log(std::to_string(p) + " - " + std::to_string(dist) + "\n");
						*smallestDist = dist;
						// I have a suspicion that this isn't right...
						*op = nextp;
					}
				}
			}

			void addPoint(size_t contour, size_t point, uint16_t mx, uint16_t my) {
				fnt::contour* c = 
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph].contours[contour]
				;
				switch (c->type) {
					default: dbg::log("Unrecognized contour type in addPoint!\n"); break;

					case fnt::contourTypeTTF: {
						fnt::ttfPoint p {};
						p.x = mx;
						p.y = my;
						p.on = true;
						p.selected = true;
						c->data.ttf.points.insert(c->data.ttf.points.begin() + point, p);
					} break;
				}
			}

			void closestPointAdd(glyph* g) {
				float smallestDist = INFINITY;
				size_t op, oc;
				float mx = g->lastCursorPos[0], my = g->lastCursorPos[1];
				/*fnt::currentFont.cv.clientPosToCanvas(mx, &mx, my, &my, g->coverage);
				mx += fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
				my += fnt::currentFont.cv.data.unscaledDim[1] / 2.f;*/
				mx = math::minf(math::maxf(mx, 0.f), fnt::currentFont.cv.data.unscaledDim[0]);
				my = math::minf(math::maxf(my, 0.f), fnt::currentFont.cv.data.unscaledDim[1]);

				fnt::glyph* fglyph = &fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph];
				for (size_t c = 0; c < fglyph->contours.size(); ++c) {
					switch (fglyph->contours[c].type) {
						default: dbg::log("Unrecognized contour type in closestPointSelect!\n"); break;

						case fnt::contourTypeTTF: {
							float prevSmallestDist = smallestDist;
							closestPointSelectTTF(&fglyph->contours[c].data.ttf, &smallestDist, &op, mx, my);
							if (prevSmallestDist > smallestDist) {
								oc = c;
							}
						} break;
					}
				}

				addPoint(oc, op, mx, my);
				g->sf->flagRender();
			}

			void newContourByPoint(glyph* g) {
				float mx = g->lastCursorPos[0], my = g->lastCursorPos[1];
				/*fnt::currentFont.cv.clientPosToCanvas(mx, &mx, my, &my, g->coverage);
				mx += fnt::currentFont.cv.data.unscaledDim[0] / 2.f;
				my += fnt::currentFont.cv.data.unscaledDim[1] / 2.f;*/
				mx = math::minf(math::maxf(mx, 0.f), fnt::currentFont.cv.data.unscaledDim[0]);
				my = math::minf(math::maxf(my, 0.f), fnt::currentFont.cv.data.unscaledDim[1]);

				cr::hst::event ev {};
				ev.type = cr::hst::eventPointsAdd;
				ev.data.pointAdd.pointsAdded = 1;
				ev.data.pointAdd.pos[0] = mx;
				ev.data.pointAdd.pos[1] = my;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;

				fnt::ttfContour ttf {};
				ttf.in = true;
				ttf.points = std::vector<fnt::ttfPoint>(2);
				ttf.points[0].x = mx;
				ttf.points[0].y = my;
				ttf.points[0].on = true;
				ttf.points[0].selected = false;
				ttf.points[1].x = mx;
				ttf.points[1].y = my;
				ttf.points[1].on = true;
				ttf.points[1].selected = true;
				fnt::contour contour {};
				contour.type = fnt::contourTypeTTF;
				contour.data.ttf = ttf;
				fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph].contours.push_back(contour);

				cr::actionState state = fnt::currentFont.acState;
				state.idle = false;
				state.ac = cr::actionGlyphMovingPoint;
				state.data.gl.selected = true;
				fnt::currentFont.changeAction(state);
				g->initCursorPos[0] = mx;
				g->initCursorPos[1] = my;
				g->sf->flagRender();

				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
			}

			void onPointAdd(void* data) {
				dbg::log("Adding point...\n");
				glyph* g = ((cr::creationScene*)data)->canvas->glyph;
				if (!fnt::currentFont.acState.data.gl.selected) {
					newContourByPoint(g);
					return;
				}

				closestPointAdd(g);
			}

			void deletePoints(fnt::glyph* g) {
				bool deincc = false;
				for (size_t c = 0; c < g->contours.size(); ++c) {
					if (deincc) {
						c -= 1;
						deincc = false;
					}

					switch (g->contours[c].type) {
						default: dbg::log("Unrecognized contour type in deletePoints!\n"); break;

						case fnt::contourTypeTTF: {
							fnt::ttfContour* ttf = &g->contours[c].data.ttf;
							bool deincp = false;
							for (size_t p = 0; p < ttf->points.size(); ++p) {
								if (deincp) {
									p -= 1;
									deincp = false;
								}
								if (ttf->points[p].selected) {
									ttf->points.erase(ttf->points.begin() + p);
									if (ttf->points.size() <= 1) {
										g->contours.erase(g->contours.begin() + c);
										deincc = true;
										break;
									}
									deincp = true;
								}
							}
						} break;
					}
				}
			}

			void onPointDelete(void* data) {
				dbg::log("Deleting point...\n");
				glyph* g = ((cr::creationScene*)data)->canvas->glyph;
				if (!fnt::currentFont.acState.data.gl.selected) {
					dbg::log("No points selected, nevermind\n");
					return;
				}

				deletePoints(&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph]);
				g->sf->flagRender();
			}
		}
	}
}