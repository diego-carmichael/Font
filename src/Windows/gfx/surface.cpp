// This file is far too large, it's okay (it's not)
#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "gfx/surface.hpp"

#include "dbg/log.hpp"
#include "Windows/gfx/d2d.hpp"
#include "Windows/gfx/window.hpp"


#include <Windows.h>
#include <vector>

gfx::surface::surface(std::string name, uint32_t width, uint32_t height) {
	this->data = malloc(sizeof(osw32::window));
	memset(this->data, 0, sizeof(osw32::window));
	osw32::window* win = (osw32::window*)this->data;
	addWinmap(win);
	win->active = true;
	win->sf = this;

	osw32::initd2d(&win->ren);

	// https://learn.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart
	WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = osw32::wndproc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(LONG_PTR);
	wc.hInstance = GetModuleHandle(NULL); // https://stackoverflow.com/a/1750095
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.lpszClassName = "DiegosGenericClassName";
	RegisterClassEx(&wc);

	win->hwnd = CreateWindow(
		wc.lpszClassName,
		name.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL, NULL, GetModuleHandle(NULL), NULL
	);
	if (!win->hwnd) {
		dbg::log("Failed to create window \"" + name + "\"\n");
		return;
	}

	SetWindowPos(
		win->hwnd, NULL, 0, 0,
		(int)width,
		(int)height,
		SWP_NOMOVE
	);
	ShowWindow(win->hwnd, SW_SHOWNORMAL);
	UpdateWindow(win->hwnd);
}

gfx::surface::~surface(void) {
	osw32::window* win = (osw32::window*)this->data;
	remWinmap(win);
	free(this->data);
}

bool gfx::surface::active(void) {
	osw32::window* win = (osw32::window*)this->data;
	return win->active;
}

void gfx::surface::update(void) {
	osw32::window* win = (osw32::window*)this->data;
	InvalidateRect(win->hwnd, NULL, FALSE);

	win->sf = this;
	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/window-messages
	MSG msg {};
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void gfx::surface::flagRender(void) {
	osw32::window* win = (osw32::window*)this->data;
	InvalidateRect(win->hwnd, NULL, FALSE);
}

void gfx::surface::renderLine(gfx::line l, gfx::col color) {
	osw32::window* win = (osw32::window*)this->data;
	osw32::brushCol(&win->ren, color);
	win->ren.target->DrawLine(
		D2D1::Point2F(l.x0, l.y0),
		D2D1::Point2F(l.x1, l.y1),
		win->ren.brush, l.width, NULL
	);
}

void gfx::surface::renderDashedLine(gfx::line l, gfx::col color) {
	osw32::window* win = (osw32::window*)this->data;
	osw32::brushCol(&win->ren, color);

	ID2D1StrokeStyle* style;
	win->ren.factory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			// All default values besides D2D1_DASH_STYLE_DASH
			D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT, D2D1_CAP_STYLE_FLAT,
			D2D1_LINE_JOIN_MITER, 10.f,
			D2D1_DASH_STYLE_DASH, 0.f
		), 0, 0, &style
	);

	win->ren.target->DrawLine(
		D2D1::Point2F(l.x0, l.y0),
		D2D1::Point2F(l.x1, l.y1),
		win->ren.brush, l.width, style
	);

	style->Release();
}

void gfx::surface::renderRect(gfx::rect r, gfx::col color) {
	osw32::window* win = (osw32::window*)this->data;
	osw32::brushCol(&win->ren, color);
	D2D1_RECT_F d2drect = D2D1::RectF(
		r.x - (r.w / 2.f),
		r.y - (r.h / 2.f),
		r.x + (r.w / 2.f),
		r.y + (r.h / 2.f)
	);
	win->ren.target->FillRectangle(&d2drect, win->ren.brush);
}

void gfx::surface::renderCircle(gfx::circle c, gfx::col color) {
	osw32::window* win = (osw32::window*)this->data;
	osw32::brushCol(&win->ren, color);
	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		D2D1::Point2F(c.x, c.y),
		c.r, c.r
	);
	win->ren.target->FillEllipse(&ellipse, win->ren.brush);
}

// https://learn.microsoft.com/en-us/windows/win32/api/d2d1/nf-d2d1-id2d1rendertarget-drawline
void gfx::surface::renderLine(gfx::point p0, gfx::point p1, gfx::col color) {
	osw32::window* win = (osw32::window*)this->data;
	osw32::brushCol(&win->ren, color);
	win->ren.target->DrawLine(
		{ p0.x, p0.y }, { p1.x, p1.y },
		win->ren.brush, 1.f, NULL
	);
}

// https://learn.microsoft.com/en-us/windows/win32/direct2d/how-to--draw-text
void gfx::surface::renderText(gfx::font* f, std::wstring str, gfx::rect bound, gfx::col color, gfx::rect* tightBound) {
	osw32::font* font = (osw32::font*)f->data;
	osw32::window* win = (osw32::window*)this->data;

	if (tightBound) {
		IDWriteTextLayout* layout;
		win->ren.write->CreateTextLayout(
			str.c_str(), str.size(),
			font->textFormat,
			bound.w, bound.h,
			&layout
		);

		DWRITE_TEXT_METRICS metrics;
		layout->GetMetrics(&metrics);
		tightBound->w = metrics.width;
		tightBound->h = metrics.height;
		tightBound->x = bound.x - (bound.w / 2.f) + (metrics.width  / 2.f);
		tightBound->y = bound.y - (bound.h / 2.f) + (metrics.height / 2.f);

		layout->Release();
		return;
	}

	osw32::brushCol(&win->ren, color);
	D2D1_RECT_F d2drect = D2D1::RectF(
		bound.x - (bound.w / 2.f),
		bound.y - (bound.h / 2.f),
		bound.x + (bound.w / 2.f),
		bound.y + (bound.h / 2.f)
	);
	win->ren.target->DrawText(
		str.c_str(), str.size(),
		font->textFormat,
		d2drect,
		win->ren.brush
	);
}

#endif