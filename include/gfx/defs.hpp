#pragma once

namespace gfx {
	typedef struct col col;
	struct col {
		float r;
		float g;
		float b;
		float a;
	};

	typedef struct rect rect;
	struct rect {
		float x;
		float y;
		float w;
		float h;
	};

	typedef struct point point;
	struct point {
		float x;
		float y;
	};
}