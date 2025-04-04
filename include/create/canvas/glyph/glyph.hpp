#pragma once

#include "gui/scene.hpp"
#include "create/infoBox/infoBox.hpp"

namespace cr {
	namespace cv {
		namespace gl {
			class glyph : public gui::element {
			public:
				gfx::surface* sf;
				gfx::rect coverage;
				ib::infoBox* box;
			public:
				glyph(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box);
				~glyph(void);
			public:
				void render(void);
				void changeCoverage(gfx::rect newCoverage);
			};
		}
	}
}