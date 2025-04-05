#include "create/logic/font.hpp"

#include "dbg/log.hpp"
#include "gfx/surface.hpp"

void fnt::defaultFontData(fnt::fontData* data) {
	data->name = "Untitled font";
	data->glyphs = std::vector<fnt::glyph>(1, { 0, std::vector<fnt::contour>(0) });

	data->glyphs[0].contours = std::vector<fnt::contour>(3);
	data->glyphs[0].contours[0].type = fnt::contourTypeTTF;
	data->glyphs[0].contours[0].data.ttf.in = true;
	data->glyphs[0].contours[0].data.ttf.points = std::vector<fnt::ttfPoint>(11, (fnt::ttfPoint){0});
		data->glyphs[0].contours[0].data.ttf.points[0].x = 86;
		data->glyphs[0].contours[0].data.ttf.points[0].y = 64;
		data->glyphs[0].contours[0].data.ttf.points[0].on = true;
		data->glyphs[0].contours[0].data.ttf.points[0].selected = true;
		data->glyphs[0].contours[0].data.ttf.points[1].x = 120;
		data->glyphs[0].contours[0].data.ttf.points[1].y = 64;
		data->glyphs[0].contours[0].data.ttf.points[1].on = true;
		data->glyphs[0].contours[0].data.ttf.points[2].x = 164;
		data->glyphs[0].contours[0].data.ttf.points[2].y = 64;
		data->glyphs[0].contours[0].data.ttf.points[2].on = false;
		data->glyphs[0].contours[0].data.ttf.points[3].x = 164;
		data->glyphs[0].contours[0].data.ttf.points[3].y = 94;
		data->glyphs[0].contours[0].data.ttf.points[3].on = true;
		data->glyphs[0].contours[0].data.ttf.points[4].x = 164;
		data->glyphs[0].contours[0].data.ttf.points[4].y = 124;
		data->glyphs[0].contours[0].data.ttf.points[4].on = false;
		data->glyphs[0].contours[0].data.ttf.points[5].x = 144;
		data->glyphs[0].contours[0].data.ttf.points[5].y = 124;
		data->glyphs[0].contours[0].data.ttf.points[5].on = true;
		data->glyphs[0].contours[0].data.ttf.points[6].x = 168;
		data->glyphs[0].contours[0].data.ttf.points[6].y = 124;
		data->glyphs[0].contours[0].data.ttf.points[6].on = false;
		data->glyphs[0].contours[0].data.ttf.points[7].x = 168;
		data->glyphs[0].contours[0].data.ttf.points[7].y = 154;
		data->glyphs[0].contours[0].data.ttf.points[7].on = true;
		data->glyphs[0].contours[0].data.ttf.points[8].x = 168;
		data->glyphs[0].contours[0].data.ttf.points[8].y = 192;
		data->glyphs[0].contours[0].data.ttf.points[8].on = false;
		data->glyphs[0].contours[0].data.ttf.points[9].x = 120;
		data->glyphs[0].contours[0].data.ttf.points[9].y = 192;
		data->glyphs[0].contours[0].data.ttf.points[9].on = true;
		data->glyphs[0].contours[0].data.ttf.points[10].x = 86;
		data->glyphs[0].contours[0].data.ttf.points[10].y = 192;
		data->glyphs[0].contours[0].data.ttf.points[10].on = true;
	data->glyphs[0].contours[1].type = fnt::contourTypeTTF;
	data->glyphs[0].contours[1].data.ttf.in = false;
	data->glyphs[0].contours[1].data.ttf.points = std::vector<fnt::ttfPoint>(7, (fnt::ttfPoint){0});
		data->glyphs[0].contours[1].data.ttf.points[0].x = 104;
		data->glyphs[0].contours[1].data.ttf.points[0].y = 78;
		data->glyphs[0].contours[1].data.ttf.points[0].on = true;
		data->glyphs[0].contours[1].data.ttf.points[1].x = 120;
		data->glyphs[0].contours[1].data.ttf.points[1].y = 78;
		data->glyphs[0].contours[1].data.ttf.points[1].on = true;
		data->glyphs[0].contours[1].data.ttf.points[2].x = 146;
		data->glyphs[0].contours[1].data.ttf.points[2].y = 78;
		data->glyphs[0].contours[1].data.ttf.points[2].on = false;
		data->glyphs[0].contours[1].data.ttf.points[3].x = 146;
		data->glyphs[0].contours[1].data.ttf.points[3].y = 96;
		data->glyphs[0].contours[1].data.ttf.points[3].on = true;
		data->glyphs[0].contours[1].data.ttf.points[4].x = 146;
		data->glyphs[0].contours[1].data.ttf.points[4].y = 118;
		data->glyphs[0].contours[1].data.ttf.points[4].on = false;
		data->glyphs[0].contours[1].data.ttf.points[5].x = 120;
		data->glyphs[0].contours[1].data.ttf.points[5].y = 118;
		data->glyphs[0].contours[1].data.ttf.points[5].on = true;
		data->glyphs[0].contours[1].data.ttf.points[6].x = 104;
		data->glyphs[0].contours[1].data.ttf.points[6].y = 118;
		data->glyphs[0].contours[1].data.ttf.points[6].on = true;
	data->glyphs[0].contours[2].type = fnt::contourTypeTTF;
	data->glyphs[0].contours[2].data.ttf.in = false;
	data->glyphs[0].contours[2].data.ttf.points = std::vector<fnt::ttfPoint>(7, (fnt::ttfPoint){0});
		data->glyphs[0].contours[2].data.ttf.points[0].x = 104;
		data->glyphs[0].contours[2].data.ttf.points[0].y = 132;
		data->glyphs[0].contours[2].data.ttf.points[0].on = true;
		data->glyphs[0].contours[2].data.ttf.points[1].x = 120;
		data->glyphs[0].contours[2].data.ttf.points[1].y = 132;
		data->glyphs[0].contours[2].data.ttf.points[1].on = true;
		data->glyphs[0].contours[2].data.ttf.points[2].x = 150;
		data->glyphs[0].contours[2].data.ttf.points[2].y = 132;
		data->glyphs[0].contours[2].data.ttf.points[2].on = false;
		data->glyphs[0].contours[2].data.ttf.points[3].x = 150;
		data->glyphs[0].contours[2].data.ttf.points[3].y = 154;
		data->glyphs[0].contours[2].data.ttf.points[3].on = true;
		data->glyphs[0].contours[2].data.ttf.points[4].x = 150;
		data->glyphs[0].contours[2].data.ttf.points[4].y = 176;
		data->glyphs[0].contours[2].data.ttf.points[4].on = false;
		data->glyphs[0].contours[2].data.ttf.points[5].x = 120;
		data->glyphs[0].contours[2].data.ttf.points[5].y = 176;
		data->glyphs[0].contours[2].data.ttf.points[5].on = true;
		data->glyphs[0].contours[2].data.ttf.points[6].x = 104;
		data->glyphs[0].contours[2].data.ttf.points[6].y = 176;
		data->glyphs[0].contours[2].data.ttf.points[6].on = true;

	data->currentGlyph = 0;
}

fnt::font::font(void) {
	fnt::defaultFontData(&this->data);
	fnt::defaultCanvasData(&this->cv.data);
	this->actionSet = cr::actionSetCanvas;
	this->action = cr::actionCanvasIdle;
}

void fnt::font::changeAction(cr::actionSet actionSet, cr::action action) {
	dbg::log(
		"[ACTION] From \"" + cr::actionStr(this->actionSet, this->action) +
		"\" to \"" + cr::actionStr(actionSet, action) + "\"\n"
	);

	cr::actionDesc desc {};
	desc.ac = this->action;
	desc.set = this->actionSet;
	this->actionSet = actionSet;
	this->action = action;
	onActionChange.call(&desc);
}

fnt::font fnt::currentFont {};
std::string currentPath = "";

void fnt::loadCurrentFont(void) {

}

void fnt::saveCurrentFont(gfx::surface* sf) {

}

void fnt::openFontButton(void* data) {
	gfx::surface* sf = (gfx::surface*)data;

	gfx::fileMenu mn {};
	mn.fileFormats.push_back({
		"Font file format", "fyi"
	});

	sf->dialogueOpenFile(&mn);
}

void fnt::saveFontButton(void* data) {
	gfx::surface* sf = (gfx::surface*)data;

	gfx::fileMenu mn {};
	mn.fileFormats.push_back({
		"Font file format", "fyi"
	});

	sf->dialogueSaveFile(&mn);
}