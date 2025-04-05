#pragma once

#include "gui/scene.hpp"
#include "create/logic/history.hpp"

namespace cr {
	namespace hst {
		class history : public gui::section {
		public:
			gfx::surface* sf;
			ev::listener* eventAddListener;
			ev::listener* eventUndoListener;
			ev::listener* eventRedoListener;
			ev::listener* keyPressListener;
		public:
			history(gfx::surface* sf);
			~history(void);
		};

		void eventAdd(ev::listener* l, void* data);
		void eventUndo(ev::listener* l, void* data);
		void eventRedo(ev::listener* l, void* data);
		void keyPress(ev::listener* l, void* data);
	}
}