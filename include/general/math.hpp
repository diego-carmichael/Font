#pragma once

namespace math {
	float minf(float f0, float f1);
	float maxf(float f0, float f1);

	float distf(float x0, float y0, float x1, float y1);

	void closestPointOnLinef(
		// Two points forming the line
		float x0, float y0, float x1, float y1,
		// Point to connect to the line
		float x2, float y2,
		// Output point
		float* x3, float* y3
	);
}