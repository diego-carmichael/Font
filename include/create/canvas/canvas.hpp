#pragma once

#include "gui/scene.hpp"
#include "create/canvas/background/background.hpp"
#include "create/canvas/metrics/metrics.hpp"
#include "create/canvas/grid/grid.hpp"
#include "create/infoBox/infoBox.hpp"

namespace cr {
	namespace cv {
		class canvasSection : public gui::section {
		public:
			gfx::surface* sf;
			bg::background* bg;
			mt::metrics* metrics;
			gr::grid* grid;
			gfx::rect coverage;
		public:
			canvasSection(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box);
			~canvasSection(void);

			void changeCoverage(gfx::rect newCoverage);
			void render(void);
		};
	}
}