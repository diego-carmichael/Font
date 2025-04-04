#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "gfx/shape.hpp"

#include "gfx/surface.hpp"
#include "Windows/gfx/window.hpp"
#include "dbg/log.hpp"

namespace osw32 {
	ID2D1PathGeometry* contourToPathGeom(window* win, gfx::contour* c) {
		ID2D1PathGeometry* geom;
		win->ren.factory->CreatePathGeometry(&geom);
		ID2D1GeometrySink* sink;
		geom->Open(&sink);

		sink->SetFillMode(D2D1_FILL_MODE_WINDING);
		sink->BeginFigure(D2D1::Point2F(c->initialX, c->initialY), D2D1_FIGURE_BEGIN_FILLED);

		for (size_t p = 0; p < c->paths.size(); ++p) {
			switch (c->paths[p].type) {
				default: dbg::log("Unrecognized shape path type! Weird!\n"); break;

				case gfx::pathTypeLine: {
					sink->AddLine(D2D1::Point2F(c->paths[p].data.line.x, c->paths[p].data.line.y));
				} break;

				case gfx::pathTypeQuadBezier: {
					D2D1_QUADRATIC_BEZIER_SEGMENT bz;
					bz.point1 = D2D1::Point2F(c->paths[p].data.quadBezier.ctrlX, c->paths[p].data.quadBezier.ctrlY);
					bz.point2 = D2D1::Point2F(c->paths[p].data.quadBezier.endX, c->paths[p].data.quadBezier.endY);
					sink->AddQuadraticBezier(&bz);
				} break;
			}
		}

		if (c->close) {
			sink->EndFigure(D2D1_FIGURE_END_CLOSED);
		} else {
			sink->EndFigure(D2D1_FIGURE_END_OPEN);
		}
		sink->Close();
		sink->Release();
		return geom;
	}
}

namespace gfx {
	// https://learn.microsoft.com/en-us/windows/win32/direct2d/direct2d-geometries-overview
	void surface::renderShape(shape* s) {
		osw32::window* win = (osw32::window*)this->data;

		std::vector<ID2D1Geometry*> geoms = std::vector<ID2D1Geometry*>(s->contours.size());
		for (size_t c = 0; c < s->contours.size(); ++c) {
			geoms[c] = contourToPathGeom(win, &s->contours[c]);
		}

		ID2D1GeometryGroup* geomGroup;
		win->ren.factory->CreateGeometryGroup(
			D2D1_FILL_MODE_WINDING,
			geoms.data(), geoms.size(), &geomGroup
		);

		if (s->shapeColor.a != 0.f) {
			osw32::brushCol(&win->ren, s->shapeColor);
			win->ren.target->FillGeometry(geomGroup, win->ren.brush);
		}
		if (s->borderThickness != 0.f && s->borderColor.a != 0.f) {
			osw32::brushCol(&win->ren, s->borderColor);
			win->ren.target->DrawGeometry(geomGroup, win->ren.brush, s->borderThickness);
		}

		geomGroup->Release();
		for (size_t g = 0; g < geoms.size(); ++g) {
			geoms[g]->Release();
		}
	}
}

#endif