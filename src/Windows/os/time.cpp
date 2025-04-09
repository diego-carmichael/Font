#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "os/time.hpp"

#include "dbg/log.hpp"

#include <Windows.h>
#include <cmath>
#include <cstdlib>
#include <vector>

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
		bool shouldCall;
	};

	std::vector<timerInfo*> timerInfos {};

	void timerCallback(void* param, BOOLEAN timerOrWaitFired) {
		timerInfo* ti = (timerInfo*)param;
		for (size_t t = 0; t < timerInfos.size(); ++t) {
			if (timerInfos[t] == ti) {
				timerInfos.erase(timerInfos.begin() + t);
				break;
			}
		}

		if (ti->shouldCall) {
			ti->callback(ti->data);
			DeleteTimerQueueTimer(timerQueue, ti->newTimer, NULL);
		}

		delete ti;
	}
}

void os::timer(os::timeSec time, void (*callback)(void*), void* data, bool stack) {
	if (osw32::timerQueue == NULL) {
		osw32::timerQueue = CreateTimerQueue();
	}

	if (!stack) {
		bool found = false;
		for (size_t t = 0; t < osw32::timerInfos.size(); ++t) {
			if (osw32::timerInfos[t]->callback == callback && 
				osw32::timerInfos[t]->data == data
			) {
				if (found) {
					osw32::timerInfos[t]->shouldCall = false;
					continue;
				}
				ChangeTimerQueueTimer(
					osw32::timerQueue,
					osw32::timerInfos[t]->newTimer,
					(DWORD)round(time * 1000.0), 0
				);
				found = true;
			}
		}
		if (found) {
			return;
		}
	}

	osw32::timerInfo* ti = new osw32::timerInfo;
	ti->callback = callback;
	ti->data = data;
	ti->shouldCall = true;
	osw32::timerInfos.push_back(ti);

	CreateTimerQueueTimer(
		&ti->newTimer, osw32::timerQueue,
		osw32::timerCallback, (void*)ti,
		(DWORD)round(time * 1000.0), 0,
		0
	);
}

void os::closeTimers(void) {
	if (osw32::timerQueue != NULL) {
		DeleteTimerQueueEx(osw32::timerQueue, NULL);
		osw32::timerQueue = NULL;
	}
}

#endif