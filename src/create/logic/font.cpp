#include "create/logic/font.hpp"

#include "dbg/log.hpp"
#include "gfx/surface.hpp"

fnt::font::font(void) {
	this->name = "Untitled font";
	this->actionSet = cr::actionSetCanvas;
	this->action = cr::actionCanvasIdle;

	this->glyphs = std::vector<fnt::glyph>(1, { 0, std::vector<fnt::contour>(0) });

	// B
	this->glyphs[0].contours = std::vector<fnt::contour>(3);
	this->glyphs[0].contours[0].type = fnt::contourTypeTTF;
	this->glyphs[0].contours[0].data.ttf.in = true;
	this->glyphs[0].contours[0].data.ttf.points = std::vector<fnt::ttfPoint>(11, (fnt::ttfPoint){0});
		this->glyphs[0].contours[0].data.ttf.points[0].x = 86;
		this->glyphs[0].contours[0].data.ttf.points[0].y = 64;
		this->glyphs[0].contours[0].data.ttf.points[0].on = true;
		this->glyphs[0].contours[0].data.ttf.points[0].selected = true;
		this->glyphs[0].contours[0].data.ttf.points[1].x = 120;
		this->glyphs[0].contours[0].data.ttf.points[1].y = 64;
		this->glyphs[0].contours[0].data.ttf.points[1].on = true;
		this->glyphs[0].contours[0].data.ttf.points[2].x = 164;
		this->glyphs[0].contours[0].data.ttf.points[2].y = 64;
		this->glyphs[0].contours[0].data.ttf.points[2].on = false;
		this->glyphs[0].contours[0].data.ttf.points[3].x = 164;
		this->glyphs[0].contours[0].data.ttf.points[3].y = 94;
		this->glyphs[0].contours[0].data.ttf.points[3].on = true;
		this->glyphs[0].contours[0].data.ttf.points[4].x = 164;
		this->glyphs[0].contours[0].data.ttf.points[4].y = 124;
		this->glyphs[0].contours[0].data.ttf.points[4].on = false;
		this->glyphs[0].contours[0].data.ttf.points[5].x = 144;
		this->glyphs[0].contours[0].data.ttf.points[5].y = 124;
		this->glyphs[0].contours[0].data.ttf.points[5].on = true;
		this->glyphs[0].contours[0].data.ttf.points[6].x = 168;
		this->glyphs[0].contours[0].data.ttf.points[6].y = 124;
		this->glyphs[0].contours[0].data.ttf.points[6].on = false;
		this->glyphs[0].contours[0].data.ttf.points[7].x = 168;
		this->glyphs[0].contours[0].data.ttf.points[7].y = 154;
		this->glyphs[0].contours[0].data.ttf.points[7].on = true;
		this->glyphs[0].contours[0].data.ttf.points[8].x = 168;
		this->glyphs[0].contours[0].data.ttf.points[8].y = 192;
		this->glyphs[0].contours[0].data.ttf.points[8].on = false;
		this->glyphs[0].contours[0].data.ttf.points[9].x = 120;
		this->glyphs[0].contours[0].data.ttf.points[9].y = 192;
		this->glyphs[0].contours[0].data.ttf.points[9].on = true;
		this->glyphs[0].contours[0].data.ttf.points[10].x = 86;
		this->glyphs[0].contours[0].data.ttf.points[10].y = 192;
		this->glyphs[0].contours[0].data.ttf.points[10].on = true;
	this->glyphs[0].contours[1].type = fnt::contourTypeTTF;
	this->glyphs[0].contours[1].data.ttf.in = false;
	this->glyphs[0].contours[1].data.ttf.points = std::vector<fnt::ttfPoint>(7, (fnt::ttfPoint){0});
		this->glyphs[0].contours[1].data.ttf.points[0].x = 104;
		this->glyphs[0].contours[1].data.ttf.points[0].y = 78;
		this->glyphs[0].contours[1].data.ttf.points[0].on = true;
		this->glyphs[0].contours[1].data.ttf.points[1].x = 120;
		this->glyphs[0].contours[1].data.ttf.points[1].y = 78;
		this->glyphs[0].contours[1].data.ttf.points[1].on = true;
		this->glyphs[0].contours[1].data.ttf.points[2].x = 146;
		this->glyphs[0].contours[1].data.ttf.points[2].y = 78;
		this->glyphs[0].contours[1].data.ttf.points[2].on = false;
		this->glyphs[0].contours[1].data.ttf.points[3].x = 146;
		this->glyphs[0].contours[1].data.ttf.points[3].y = 96;
		this->glyphs[0].contours[1].data.ttf.points[3].on = true;
		this->glyphs[0].contours[1].data.ttf.points[4].x = 146;
		this->glyphs[0].contours[1].data.ttf.points[4].y = 118;
		this->glyphs[0].contours[1].data.ttf.points[4].on = false;
		this->glyphs[0].contours[1].data.ttf.points[5].x = 120;
		this->glyphs[0].contours[1].data.ttf.points[5].y = 118;
		this->glyphs[0].contours[1].data.ttf.points[5].on = true;
		this->glyphs[0].contours[1].data.ttf.points[6].x = 104;
		this->glyphs[0].contours[1].data.ttf.points[6].y = 118;
		this->glyphs[0].contours[1].data.ttf.points[6].on = true;
	this->glyphs[0].contours[2].type = fnt::contourTypeTTF;
	this->glyphs[0].contours[2].data.ttf.in = false;
	this->glyphs[0].contours[2].data.ttf.points = std::vector<fnt::ttfPoint>(7, (fnt::ttfPoint){0});
		this->glyphs[0].contours[2].data.ttf.points[0].x = 104;
		this->glyphs[0].contours[2].data.ttf.points[0].y = 132;
		this->glyphs[0].contours[2].data.ttf.points[0].on = true;
		this->glyphs[0].contours[2].data.ttf.points[1].x = 120;
		this->glyphs[0].contours[2].data.ttf.points[1].y = 132;
		this->glyphs[0].contours[2].data.ttf.points[1].on = true;
		this->glyphs[0].contours[2].data.ttf.points[2].x = 150;
		this->glyphs[0].contours[2].data.ttf.points[2].y = 132;
		this->glyphs[0].contours[2].data.ttf.points[2].on = false;
		this->glyphs[0].contours[2].data.ttf.points[3].x = 150;
		this->glyphs[0].contours[2].data.ttf.points[3].y = 154;
		this->glyphs[0].contours[2].data.ttf.points[3].on = true;
		this->glyphs[0].contours[2].data.ttf.points[4].x = 150;
		this->glyphs[0].contours[2].data.ttf.points[4].y = 176;
		this->glyphs[0].contours[2].data.ttf.points[4].on = false;
		this->glyphs[0].contours[2].data.ttf.points[5].x = 120;
		this->glyphs[0].contours[2].data.ttf.points[5].y = 176;
		this->glyphs[0].contours[2].data.ttf.points[5].on = true;
		this->glyphs[0].contours[2].data.ttf.points[6].x = 104;
		this->glyphs[0].contours[2].data.ttf.points[6].y = 176;
		this->glyphs[0].contours[2].data.ttf.points[6].on = true;

	this->currentGlyph = 0;
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