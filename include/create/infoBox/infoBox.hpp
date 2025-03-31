#pragma once

#include "gui/scene.hpp"
#include "gfx/surface.hpp"

namespace cr {
	namespace ib {
		class infoBox : public gui::section {
		public:
			gfx::surface* sf;
			gfx::font font;
		public:
			infoBox(gfx::surface* sf, gfx::font font);
			~infoBox(void);

			void render(void);
		};
	}
}