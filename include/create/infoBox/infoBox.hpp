#pragma once

#include "gui/scene.hpp"
#include "gfx/surface.hpp"

namespace cr {
	namespace ib {
		class infoBox : public gui::section {
		public:
			gfx::surface* sf;
			gfx::font font;

			float displayTime;
			std::wstring text;
			bool shouldRender;
			gfx::rect bgRect;

			ev::listener* cursorMoveListener;
			ev::listener* rightClickMenuAppearListener;
		public:
			infoBox(gfx::surface* sf, gfx::font font);
			~infoBox(void);

			void render(void);
			void setText(std::wstring s);
		};

		void resetText(void* data);
		void cursorMove(ev::listener* l, void* data);
		void rightClickMenuAppear(ev::listener* l, void* data);
	}
}