#include "os/iden.hpp"
#ifdef OS_WINDOWS
#include "Windows/gfx/d2d.hpp"

#include "dbg/log.hpp"
#include "gfx/surface.hpp"
#include "Windows/gfx/window.hpp"

// Mostly taken from:
// https://learn.microsoft.com/en-us/windows/win32/direct2d/direct2d-quickstart
// https://learn.microsoft.com/en-us/windows/win32/direct2d/how-to--draw-text

void osw32::initd2d(osw32::d2d* ren) {
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED, &ren->factory
	);
	if (!SUCCEEDED(hr)) {
		dbg::log("[BAD] D2D1CreateFactory returned " + std::to_string(hr) + "\n");
	}
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(ren->write),
		reinterpret_cast<IUnknown**>(&ren->write)
	);
	if (!SUCCEEDED(hr)) {
		dbg::log("[BAD] DWriteCreateFactory" + std::to_string(hr) + "\n");
	}

	dbg::log("initd2d done\n");
}

void osw32::created2dTarget(osw32::d2d* ren, HWND hwnd) {
	RECT rc;
	GetClientRect(hwnd, &rc);
	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top
	);
	HRESULT hr = ren->factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, size),
		&ren->target
	);
	if (!SUCCEEDED(hr)) {
		dbg::log("CreateHwndRenderTarget returned " + std::to_string(hr) + "\n");
	}

	ren->brushCol.r = 1.f;
	ren->brushCol.g = 1.f;
	ren->brushCol.b = 1.f;
	ren->brushCol.a = 1.f;
	ren->target->CreateSolidColorBrush(
		D2D1::ColorF(1.f, 1.f, 1.f, 1.f),
		&ren->brush
	);
}

void osw32::termd2d(osw32::d2d* ren) {
	if (ren->target) {
		if (ren->write) {
			ren->write->Release();
		}
		ren->brush->Release();
		ren->target->Release();
	}
}

void osw32::resized2d(osw32::d2d* ren, UINT width, UINT height, gfx::surface* sf) {
	if (ren->target) {
		ren->target->Resize(D2D1::SizeU(width, height));
	}
	sf->onResize.call(0);
}

void osw32::paintd2d(osw32::d2d* ren, HWND hwnd, gfx::col color, gfx::surface* sf) {
	if (!ren->target) {
		osw32::created2dTarget(ren, hwnd);
	}

	ren->target->BeginDraw();
	ren->target->Clear(D2D1::ColorF(color.r, color.g, color.b, 1.f));

	sf->onRender.call(0);

	ren->target->EndDraw();
}

void osw32::brushCol(osw32::d2d* ren, gfx::col color) {
	if (
		color.r != ren->brushCol.r ||
		color.g != ren->brushCol.g ||
		color.b != ren->brushCol.b ||
		color.a != ren->brushCol.a
	) {
		ren->brush->SetColor(
			D2D1::ColorF(color.r, color.g, color.b, color.a)
		);
		ren->brushCol = color;
	}
}

// https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/DirectWrite/font-enumeration.md
size_t gfx::surface::getNumFonts(void) {
	osw32::window* win = (osw32::window*)this->data;

	IDWriteFontCollection* fontCollection;
	win->ren.write->GetSystemFontCollection(&fontCollection);
	UINT32 numFonts = fontCollection->GetFontFamilyCount();
	fontCollection->Release();
	return (size_t)numFonts;
}

// https://github.com/MicrosoftDocs/win32/blob/docs/desktop-src/DirectWrite/font-enumeration.md
void gfx::surface::getFontInfo(size_t i, gfx::fontInfo* f) {
	osw32::window* win = (osw32::window*)this->data;
	IDWriteFontCollection* fontCollection;
	win->ren.write->GetSystemFontCollection(&fontCollection);
	IDWriteFontFamily* fontFamily;
	fontCollection->GetFontFamily(i, &fontFamily);
	IDWriteLocalizedStrings* familyNames;
	fontFamily->GetFamilyNames(&familyNames);

	UINT32 localeIndex = 0;
	BOOL exists = false;
	wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
	int localeSuccess = GetUserDefaultLocaleName(
		localeName, LOCALE_NAME_MAX_LENGTH
	);
	if (localeSuccess) {
		familyNames->FindLocaleName(localeName, &localeIndex, &exists);
	}
	if (!exists) {
		familyNames->FindLocaleName(L"en-us", &localeIndex, &exists);
	}
	if (!exists) {
		localeIndex = 0;
	}

	UINT32 length = 0;
	familyNames->GetStringLength(localeIndex, &length);
	wchar_t* name = new wchar_t[length+1];
	familyNames->GetString(localeIndex, name, length+1);
	f->name = std::wstring(name);

	familyNames->Release();
	fontFamily->Release();
	fontCollection->Release();
}

// https://stackoverflow.com/a/35338788
size_t gfx::surface::getDefaultFont(void) {
	/*NONCLIENTMETRICS metr;
	metr.cbSize = sizeof(NONCLIENTMETRICS);
	SystemParametersInfo(
		SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS), &metr,
		0
	);*/
	// ^ Can't figure this out :(

	size_t numFonts = this->getNumFonts();
	for (size_t f = 0; f < numFonts; ++f) {
		fontInfo info;
		this->getFontInfo(f, &info);
		if (info.name == L"Segoe UI") {
			return f;
		}
	}
	return 0;
}

// https://learn.microsoft.com/en-us/windows/win32/direct2d/how-to--draw-text
gfx::font gfx::surface::loadFont(size_t i, float pointSize) {
	osw32::window* win = (osw32::window*)this->data;
	gfx::font font;
	font.data = new osw32::font;
	osw32::font* w32Font = (osw32::font*)font.data;

	gfx::fontInfo info;
	this->getFontInfo(i, &info);

	win->ren.write->CreateTextFormat(
		info.name.c_str(), NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		(pointSize / 72.f) * 96.f,
		L"", &w32Font->textFormat
	);

	dbg::wlog(L"Loaded font \"" + info.name + L"\" at point size " + std::to_wstring(pointSize) + L"\n");
	return font;
}

void gfx::surface::deloadFont(gfx::font* f) {
	osw32::font* w32Font = (osw32::font*)f->data;
	w32Font->textFormat->Release();
	delete w32Font;
}

#endif