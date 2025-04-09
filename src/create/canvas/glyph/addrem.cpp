// This file is great don't worry about it
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

				cr::hst::event ev {};
				ev.type = cr::hst::eventPointsAdd;
				ev.data.pointAdd.pointsAdded = 1;
				ev.data.pointAdd.pos[0] = mx;
				ev.data.pointAdd.pos[1] = my;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;
				addPoint(oc, op, mx, my);
				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
				g->sf->flagRender();
			}

			void newContourByPoint(glyph* g) {
				float mx = g->lastCursorPos[0], my = g->lastCursorPos[1];
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

				ev.newFont = g->prevFont = fnt::currentFont.data;
				ev.newCanvas = g->prevCanvas = fnt::currentFont.cv.data;
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

			void deletePoints(fnt::glyph* g, cr::hst::pointRemoveData* data) {
				bool deincc = false;
				for (size_t c = 0; c <= g->contours.size(); ++c) {
					if (deincc) {
						c -= 1;
						deincc = false;
					}
					if (c == g->contours.size()) {
						break;
					}

					switch (g->contours[c].type) {
						default: dbg::log("Unrecognized contour type in deletePoints!\n"); break;

						case fnt::contourTypeTTF: {
							fnt::ttfContour* ttf = &g->contours[c].data.ttf;
							bool deincp = false;
							for (size_t p = 0; p <= ttf->points.size(); ++p) {
								if (deincp) {
									p -= 1;
									deincp = false;
								}
								if (p == ttf->points.size()) {
									break;
								}
								if (ttf->points[p].selected) {
									data->pointsRemoved += 1;
									if (data->pointsRemoved == 1) {
										data->pos[0] = ttf->points[p].x;
										data->pos[1] = ttf->points[p].y;
									}
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

				cr::hst::event ev {};
				ev.type = cr::hst::eventPointsRemove;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;
				deletePoints(
					&fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph],
					&ev.data.pointRemove
				);
				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
				g->sf->flagRender();
			}

			void onPointSwitch(glyph* g, cr::hst::pointSwitchData* data, bool on) {
				data->on = on;
				fnt::glyph* fglyph = &fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph];
				for (size_t c = 0; c < fglyph->contours.size(); ++c) {
					switch (fglyph->contours[c].type) {
						default: dbg::log("Unrecognized contour type in onPointSwitch!\n"); break;

						case fnt::contourTypeTTF: {
							fnt::ttfContour* ttf = &fglyph->contours[c].data.ttf;
							for (size_t p = 0; p < ttf->points.size(); ++p) {
								if (ttf->points[p].selected && ttf->points[p].on != on) {
									data->pointsSwitched += 1;
									if (data->pointsSwitched == 1) {
										data->pos[0] = ttf->points[p].x;
										data->pos[1] = ttf->points[p].y;
									}
									ttf->points[p].on = on;
								}
							}
						} break;
					}
				}
			}

			void onPointSwitchOn(void* data) {
				dbg::log("Switching points on...\n");
				glyph* g = ((cr::creationScene*)data)->canvas->glyph;
				if (!fnt::currentFont.acState.data.gl.selected) {
					dbg::log("No points selected, nevermind\n");
					return;
				}

				cr::hst::event ev {};
				ev.type = cr::hst::eventPointsSwitch;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;
				onPointSwitch(g, &ev.data.pointSwitch, true);
				if (ev.data.pointSwitch.pointsSwitched == 0) {
					dbg::log("No points switched, nevermind\n");
					return;
				}
				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
				g->sf->flagRender();
			}

			void onPointSwitchOff(void* data) {
				dbg::log("Switching points off...\n");
				glyph* g = ((cr::creationScene*)data)->canvas->glyph;
				if (!fnt::currentFont.acState.data.gl.selected) {
					dbg::log("No points selected, nevermind\n");
					return;
				}

				cr::hst::event ev {};
				ev.type = cr::hst::eventPointsSwitch;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;
				onPointSwitch(g, &ev.data.pointSwitch, false);
				if (ev.data.pointSwitch.pointsSwitched == 0) {
					dbg::log("No points switched, nevermind\n");
					return;
				}
				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
				g->sf->flagRender();
			}

			void onContourSwitch(glyph* g, cr::hst::contourSwitchData* data, bool in) {
				data->in = in;
				fnt::glyph* fglyph = &fnt::currentFont.data.glyphs[fnt::currentFont.data.currentGlyph];
				for (size_t c = 0; c < fglyph->contours.size(); ++c) {
					switch (fglyph->contours[c].type) {
						default: dbg::log("Unrecognized contour type in onContourSwitch!\n"); break;

						case fnt::contourTypeTTF: {
							bool selected = false;
							fnt::ttfContour* ttf = &fglyph->contours[c].data.ttf;
							for (size_t p = 0; p < ttf->points.size(); ++p) {
								if (ttf->points[p].selected) {
									selected = true;
									break;
								}
							}

							if ((!selected) || (ttf->in == in)) {
								continue;
							}
							data->contoursSwitched += 1;
							ttf->in = in;
						} break;
					}
				}
			}

			void onContourSwitchIn(void* data) {
				dbg::log("Switching contour inside...\n");
				glyph* g = ((cr::creationScene*)data)->canvas->glyph;
				if (!fnt::currentFont.acState.data.gl.selected) {
					dbg::log("No points selected, nevermind\n");
					return;
				}

				cr::hst::event ev {};
				ev.type = cr::hst::eventContourSwitch;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;
				onContourSwitch(g, &ev.data.contourSwitch, true);
				if (ev.data.contourSwitch.contoursSwitched == 0) {
					dbg::log("No contours switched, nevermind\n");
					return;
				}
				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
				g->sf->flagRender();
			}

			void onContourSwitchOut(void* data) {
				dbg::log("Switching contour inside...\n");
				glyph* g = ((cr::creationScene*)data)->canvas->glyph;
				if (!fnt::currentFont.acState.data.gl.selected) {
					dbg::log("No points selected, nevermind\n");
					return;
				}

				cr::hst::event ev {};
				ev.type = cr::hst::eventContourSwitch;
				ev.prevFont = fnt::currentFont.data;
				ev.prevCanvas = fnt::currentFont.cv.data;
				onContourSwitch(g, &ev.data.contourSwitch, false);
				if (ev.data.contourSwitch.contoursSwitched == 0) {
					dbg::log("No contours switched, nevermind\n");
					return;
				}
				ev.newFont = fnt::currentFont.data;
				ev.newCanvas = fnt::currentFont.cv.data;
				cr::hst::addEvent(&ev);
				g->sf->flagRender();
			}
		}
	}
}