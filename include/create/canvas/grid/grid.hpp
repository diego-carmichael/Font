#pragma once

#include "gui/scene.hpp"
#include "general/event.hpp"

namespace cr {
	namespace cv {
		namespace gr {
			class grid : public gui::element {
			public:
				gfx::surface* sf;
				gfx::rect coverage;
			public:
				grid(gfx::surface* sf, gfx::rect coverage);
				~grid(void);
				void render(void);
				void changeCoverage(gfx::rect coverage);
			};
		}
	}
}