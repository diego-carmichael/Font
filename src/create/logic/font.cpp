#include "create/logic/font.hpp"

#include "dbg/log.hpp"
#include "gfx/surface.hpp"

fnt::font::font(void) {
	this->name = "Untitled font";
	this->actionSet = cr::actionSetCanvas;
	this->action = cr::actionCanvasIdle;

	this->glyphs = std::vector<fnt::glyph>(1, { 0, std::vector<fnt::contour>(0) });
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