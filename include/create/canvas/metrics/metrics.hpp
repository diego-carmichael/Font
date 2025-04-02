#pragma once

#include "gui/scene.hpp"

namespace cr {
	namespace cv {
		namespace mt {
			class metrics : public gui::element {
			public:
				gfx::surface* sf;
				gfx::rect coverage;
			public:
				metrics(gfx::surface* sf, gfx::rect coverage);
				~metrics(void);

				void render(void);
				void changeCoverage(gfx::rect coverage);
			};
		}
	}
}