#pragma once

#include "gfx/shape.hpp"

#include <vector>
#include <cstdint>

namespace fnt {
	typedef uint8_t contourType;
	const contourType contourTypeUnknown = 0;

	const contourType contourTypeTTF = 1;
	typedef struct ttfPoint ttfPoint;
	struct ttfPoint {
		uint16_t x;
		uint16_t y;
		bool on;
	};
	typedef struct ttfContour ttfContour;
	struct ttfContour {
		std::vector<ttfPoint> points;
		bool in;
	};

	// Has to be a struct cuz vector :(
	typedef struct contourData contourData;
	struct contourData {
		ttfContour ttf;
	};
	typedef struct contour contour;
	struct contour {
		contourType type;
		contourData data;
	};

	typedef struct glyph glyph;
	struct glyph {
		uint32_t codepoint;
		std::vector<contour> contours;
	};
}