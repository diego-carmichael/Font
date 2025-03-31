#include "general/event.hpp"

#include "dbg/log.hpp"

ev::event::event(void) {

}

ev::event::~event(void) {
	if (this->listeners.size() != 0) {
		dbg::log("Event removed with active listeners! Weird!\n");
	}
}

ev::listener* ev::event::addListener(void* data, void (*call)(ev::listener*, void*)) {
	ev::listener* newListener = new ev::listener;
	newListener->data = data;
	newListener->call = call;
	this->listeners.push_back(newListener);
	return newListener;
}

void ev::event::removeListener(ev::listener* l) {
	for (size_t li = 0; li < this->listeners.size(); ++li) {
		if (this->listeners[li] == l) {
			this->listeners.erase(this->listeners.begin()+li);
			delete l;
			return;
		}
	}
	dbg::log("Call to remove non-existent listener! Weird!\n");
}

void ev::event::call(void* data) {
	for (size_t li = 0; li < this->listeners.size(); ++li) {
		if (this->listeners[li]->call) {
			this->listeners[li]->call(this->listeners[li], data);
		}
	}
}