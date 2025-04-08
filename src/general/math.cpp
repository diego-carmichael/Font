#include "general/math.hpp"

#include <cmath>

namespace math {
	float minf(float f0, float f1) {
		return (f0 < f1) ?(f0) :(f1);
	}
	float maxf(float f0, float f1) {
		return (f0 > f1) ?(f0) :(f1);
	}

	float distf(float x0, float y0, float x1, float y1) {
		return sqrtf((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
	}

	void closestPointOnLinef(
		// Two points forming the line
		float x0, float y0, float x1, float y1,
		// Point to connect to the line
		float x2, float y2,
		// Output point
		float* x3, float* y3
	) {
		if (x0 == x1) {
			x0 += 0.0001f;
		}
		if (y0 == y1) {
			y0 += 0.0001f;
		}

		// Figured this out myself, I think there's a better
		// way of doing this... too bad!
		float g0 = (x1 - x0) / (y1 - y0);
		float g1 = (y1 - y0) / (x1 - x0);
		float n = (((g0 * x2) + y2) + ((g1 * x0) - y0)) / (g1 + g0);
		*x3 = maxf(minf(n, maxf(x0, x1)), minf(x0, x1));
		*y3 = (g1 * (*x3 - x0)) + y0;
	}
}