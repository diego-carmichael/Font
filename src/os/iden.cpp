#include "os/iden.hpp"

const os::type os::typeUnknown = 0;
const os::type os::typeWindows = 1;

os::type os::getCurrentType(void) {
	#ifdef OS_WINDOWS
		return os::typeWindows;
	#else
		return os::typeUnknown;
	#endif
}