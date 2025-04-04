#pragma once

#include <cstdint>
#include <vector>

#include "gfx/defs.hpp"

namespace gfx {
	typedef uint8_t pathType;
	const pathType pathTypeUnknown = 0;

	const pathType pathTypeLine = 1;
	typedef struct linePath linePath;
	struct linePath {
		float x;
		float y;
	};

	const pathType pathTypeQuadBezier = 2;
	typedef struct quadBezierPath quadBezierPath;
	struct quadBezierPath {
		float ctrlX;
		float ctrlY;
		float endX;
		float endY;
	};

	// Could be union, but unfortunately, vector -_-
	typedef struct pathData pathData;
	struct pathData {
		linePath line;
		quadBezierPath quadBezier;
	};

	typedef struct path path;
	struct path {
		pathType type;
		pathData data;
	};

	typedef struct contour contour;
	struct contour {
		// Clockwise = fill
		// Counter-clockwise = don't fill
		float initialX;
		float initialY;
		bool close;
		std::vector<path> paths;
	};

	typedef struct shape shape;
	struct shape {
		col shapeColor;
		col borderColor;
		float borderThickness;
		std::vector<contour> contours;
	};
}