#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "os/time.hpp"

#include <Windows.h>
#include <cmath>
#include <cstdlib>

void os::sleep(os::timeSec time) {
	Sleep((DWORD)round(time * 1000.0));
}

namespace osw32 {
	HANDLE timerQueue = NULL;

	typedef struct timerInfo timerInfo;
	struct timerInfo {
		HANDLE newTimer;
		void (*callback)(void*);
		void* data;
	};

	void timerCallback(void* param, BOOLEAN timerOrWaitFired) {
		timerInfo* ti = (timerInfo*)param;
		ti->callback(ti->data);
		DeleteTimerQueueTimer(timerQueue, ti->newTimer, NULL);
	}
}

void os::timer(os::timeSec time, void (*callback)(void*), void* data) {
	if (osw32::timerQueue == NULL) {
		osw32::timerQueue = CreateTimerQueue();
	}

	osw32::timerInfo* ti = new osw32::timerInfo;
	ti->callback = callback;
	ti->data = data;

	CreateTimerQueueTimer(
		&ti->newTimer, osw32::timerQueue,
		osw32::timerCallback, (void*)ti,
		(DWORD)round(time * 1000.0), 0,
		0
	);
}

#endif