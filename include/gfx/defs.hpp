#pragma once

namespace gfx {
	typedef struct col col;
	struct col {
		float r;
		float g;
		float b;
		float a;
	};

	typedef struct line line;
	struct line {
		float x0;
		float y0;
		float x1;
		float y1;
		float width;
	};

	typedef struct rect rect;
	struct rect {
		float x;
		float y;
		float w;
		float h;
	};

	typedef struct circle circle;
	struct circle {
		float x;
		float y;
		float r;
	};

	typedef struct point point;
	struct point {
		float x;
		float y;
	};
}