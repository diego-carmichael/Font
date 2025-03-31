#pragma once

#include "gui/scene.hpp"
#include "create/canvas/background/background.hpp"
#include "create/canvas/grid/grid.hpp"

namespace cr {
	namespace cv {
		class canvasSection : public gui::section {
		public:
			gfx::surface* sf;
			bg::background* bg;
			gr::grid* grid;
			ev::listener* renderListener;
			ev::listener* changedListener;
			gfx::rect coverage;
		public:
			canvasSection(gfx::surface* sf, gfx::rect coverage);
			~canvasSection(void);

			void changeCoverage(gfx::rect newCoverage);
			void render(void);
		};
	}
}