#include "create/logic/font.hpp"

#include "dbg/log.hpp"
#include "gfx/surface.hpp"

fnt::font::font(void) {
	this->name = "Untitled font";
	this->actionSet = cr::actionSetCanvas;
	this->action = cr::actionCanvasIdle;
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