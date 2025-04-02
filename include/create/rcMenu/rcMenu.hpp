#pragma once

#include "gui/scene.hpp"

namespace cr {
	namespace rc {
		class rcMenu : public gui::section {
		public:
			gfx::surface* sf;
			ev::listener* actionChangeListener;

		public:
			rcMenu(gfx::surface* sf);
			~rcMenu(void);

			void process(void);
		};

		void actionChange(ev::listener* l, void* data);

		void changeToCanvas(void* data);
		void changeToEdit(void* data);
	}
}