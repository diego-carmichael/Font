#pragma once

#include <vector>

namespace ev {
	typedef struct listener listener;
	struct listener {
		void* data;
		void (*call)(listener*, void*);
	};

	class event {
	private:
		std::vector<listener*> listeners {};
	public:
		event(void);
		~event(void);
		listener* addListener(void* data, void (*call)(listener*, void*));
		void removeListener(listener* l); // Deletes memory for l btw
		void call(void* data);
	};
}