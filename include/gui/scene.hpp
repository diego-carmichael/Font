#pragma once

#include "gfx/surface.hpp"
#include "gfx/defs.hpp"

namespace gui {
	class element {
	public:
		void (*render)(gfx::surface* sf);
	};

	class section {
	public:
		gfx::rect coverage;
	};

	class scene {
	public:
		std::vector<section> sections {};
	};
}