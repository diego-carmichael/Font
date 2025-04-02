#pragma once

namespace os {
	typedef double timeSec;

	void sleep(timeSec time);
	void timer(timeSec time, void (*callback)(void*), void* data, bool stack);
	void closeTimers(void);
}