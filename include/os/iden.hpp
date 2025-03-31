#pragma once

#include <cstdint>

#define OS_TYPE_WINDOWS 1
#ifdef _WIN32
#define OS_WINDOWS
#endif

namespace os {
	typedef uint8_t type;
	extern const type typeUnknown;
	extern const type typeWindows;

	type getCurrentType(void);
}