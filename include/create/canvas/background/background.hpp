#pragma once

#include "gui/scene.hpp"
#include "general/event.hpp"

namespace cr {
	namespace cv {
		namespace bg {
			class background : public gui::element {
			public:
				gfx::surface* sf;
				ev::listener* mousePressListener;
				ev::listener* mouseReleaseListener;
				ev::listener* cursorMoveListener;
				ev::listener* cursorScrollListener;
				gfx::rect coverage;
			public:
				background(gfx::surface* sf, gfx::rect coverage);
				~background(void);
				void render(background* bg);
				void changeCoverage(gfx::rect coverage);
			public:
				float lastCursorPos[2];
			};

			void mousePress(ev::listener* l, void* data);
			void mouseRelease(ev::listener* l, void* data);
			void cursorMove(ev::listener* l, void* data);
			void cursorScroll(ev::listener* l, void* data);
		}
	}
}