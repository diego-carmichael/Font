#pragma once

#include "gfx/defs.hpp"
#include "gfx/surface.hpp"

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

namespace osw32 {
	typedef struct d2d d2d;
	struct d2d {
		ID2D1Factory* factory;
		ID2D1HwndRenderTarget* target;
		ID2D1SolidColorBrush* brush;
		gfx::col brushCol;
		IDWriteFactory* write;
	};

	typedef struct font font;
	struct font {
		IDWriteTextFormat* textFormat;
	};

	void initd2d(d2d* ren);
	void termd2d(d2d* ren);

	void created2dTarget(d2d* ren, HWND hwnd); // (Internal usage)

	void resized2d(d2d* ren, UINT width, UINT height, gfx::surface* sf);
	void paintd2d(d2d* ren, HWND hwnd, gfx::col color, gfx::surface* sf);
	void brushCol(d2d* ren, gfx::col color);
}