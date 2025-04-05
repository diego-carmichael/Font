#include "create/history/history.hpp"

#include "dbg/log.hpp"

namespace cr {
	namespace hst {
		history::history(gfx::surface* sf) {
			hst::clearEvents();
			this->sf = sf;

			this->eventAddListener = hst::onEventAdd.addListener(
				(void*)this, eventAdd
			);
			this->eventUndoListener = hst::onEventUndo.addListener(
				(void*)this, eventUndo
			);
			this->eventRedoListener = hst::onEventRedo.addListener(
				(void*)this, eventRedo
			);
			this->keyPressListener = sf->onKeyPress.addListener(
				(void*)this, keyPress
			);
		}

		history::~history(void) {
			this->sf->onKeyPress.removeListener(this->keyPressListener);
			hst::onEventRedo.removeListener(this->eventRedoListener);
			hst::onEventUndo.removeListener(this->eventUndoListener);
			hst::onEventAdd.removeListener(this->eventAddListener);
			hst::clearEvents();
		}

		void eventAdd(ev::listener* l, void* data) {
			history* h = (history*)l->data;
			h->sf->flagRender();

			hst::event* ev = (hst::event*)data;
			dbg::log("[HISTORY] " + 
				hst::eventOccurString(ev->type, &ev->data)
				+ "\n"
			);
		}

		void eventUndo(ev::listener* l, void* data) {
			history* h = (history*)l->data;
			h->sf->flagRender();

			hst::event* ev = (hst::event*)data;
			dbg::log("[HISTORY] " + 
				hst::eventUndoString(ev->type, &ev->data)
				+ "\n"
			);
		}

		void eventRedo(ev::listener* l, void* data) {
			history* h = (history*)l->data;
			h->sf->flagRender();

			hst::event* ev = (hst::event*)data;
			dbg::log("[HISTORY] " + 
				hst::eventRedoString(ev->type, &ev->data)
				+ "\n"
			);
		}

		void keyPress(ev::listener* l, void* data) {
			history* h = (history*)l->data;
			gfx::inp::keyboardKey key = (gfx::inp::keyboardKey)((size_t)data);
			if (key == gfx::inp::keyboardZ && h->sf->isKeyDown(gfx::inp::keyboardLCtrl)) {
				cr::hst::undoEvent();
			}
			if (key == gfx::inp::keyboardY && h->sf->isKeyDown(gfx::inp::keyboardLCtrl)) {
				cr::hst::redoEvent();
			}
		}
	}
}