#include "general/math.hpp"

namespace math {
	float minf(float f0, float f1) {
		return (f0 < f1) ?(f0) :(f1);
	}
	float maxf(float f0, float f1) {
		return (f0 > f1) ?(f0) :(f1);
	}
}