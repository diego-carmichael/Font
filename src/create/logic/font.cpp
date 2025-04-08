#include "create/logic/font.hpp"

#include "dbg/log.hpp"
#include "gfx/surface.hpp"
#include "general/yak.hpp"
#include "general/string.hpp"
#include "general/bytes.hpp"

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
std::string fnt::currentPath = "";

ev::event fnt::onFontOpen {};
void fnt::loadCurrentFont(std::string filename) {
	int res = fnt::openFile(
		filename.c_str(),
		&fnt::currentFont.data, &fnt::currentFont.cv.data
	);
	if (res != 0) {
		dbg::log("Unable to open file!!\n");
		return;
	}

	fnt::currentPath = filename;
	dbg::log("Font successfully loaded\n");
	onFontOpen.call(0);
}

ev::event fnt::onFontClose {};
void fnt::saveCurrentFont(std::string filename) {
	int res = fnt::saveFile(
		filename.c_str(),
		&fnt::currentFont.data, &fnt::currentFont.cv.data
	);
	if (res != 0) {
		dbg::log("Unable to save file!!\n");
		return;
	}

	fnt::currentPath = filename;
	dbg::log("Font successfully saved\n");
	onFontClose.call(0);
}

void fnt::openFontButton(void* data) {
	gfx::surface* sf = (gfx::surface*)data;

	gfx::fileMenu mn {};
	mn.fileFormats.push_back({
		"Font file format", "fyi"
	});

	std::string s = sf->dialogueOpenFile(&mn);
	if (s.length() == 0) {
		return;
	}

	dbg::log("Opening font...\n");
	fnt::loadCurrentFont(s);
}

void fnt::saveFontButton(void* data) {
	gfx::surface* sf = (gfx::surface*)data;

	gfx::fileMenu mn {};
	mn.fileFormats.push_back({
		"Font file format", "fyi"
	});

	std::string s = sf->dialogueSaveFile(&mn);
	if (s.length() == 0) {
		return;
	}

	dbg::log("Saving font...\n");
	fnt::saveCurrentFont(s);
}

int fnt::openFile(
	const char* filename,
	fnt::fontData* fdata, fnt::canvasData* cdata
) {
	*fdata = (fnt::fontData){};
	*cdata = (fnt::canvasData){};

	yak::file file;
	if (readFile(filename, &file) != 0) {
		return -1;
	}

	// Diego...
	file.claimer = 0x446965676F2E2E2E;
	// Font....
	file.identif = 0x466F6E742E2E2E2E;

	// font...1
	if (file.c.id != 0x666F6E742E2E2E31) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("font...1 chunk ID invalid\n");
		return -1;
	}
	fdata->name = "";
	str::readUTF8(file.c.data, &fdata->name);
	dbg::log("\"" + fdata->name + "\"\n");

	// cnvs...1
	yak::chunk* c = yak::findChunk(&file.c, 0x636E76732E2E2E31, 0);
	if (!c) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("No 'cnvs...1' chunk found\n");
		return -1;
	}
	if (c->data.size() != 10) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Invalid 'cnvs...1' size\n");
		return -1;
	}

	cdata->unscaledDim[0] = byte::be::readu16(c->data.data());
	if (cdata->unscaledDim[0] > maxUnscaledDim[0]) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Canvas width too large\n");
		return -1;
	}
	if (cdata->unscaledDim[0] < minUnscaledDim[0]) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Canvas width too small\n");
		return -1;
	}

	cdata->unscaledDim[1] = byte::be::readu16(c->data.data()+2);
	if (cdata->unscaledDim[1] > maxUnscaledDim[1]) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Canvas height too large\n");
		return -1;
	}
	if (cdata->unscaledDim[1] < minUnscaledDim[1]) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Canvas height too small\n");
		return -1;
	}

	cdata->ascender = byte::be::readu16(c->data.data()+4);
	cdata->descender = byte::be::readu16(c->data.data()+6);
	cdata->lineGap = byte::be::readu16(c->data.data()+8);
	if (!fnt::validateMetrics(cdata)) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Invalid canvas metrics\n");
		return -1;
	}

	// glfs...1
	c = yak::findChunk(&file.c, 0x676C66732E2E2E31, 0);
	if (!c) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("No 'glfs...1' chunk found\n");
		return -1;
	}
	uint16_t dim[2] = {
		(uint16_t)cdata->unscaledDim[0],
		(uint16_t)cdata->unscaledDim[1]
	};
	for (size_t ic = 0; ic < c->children.size(); ++ic) {
		switch (c->children[ic].id) {
			default: break;

			// glyf...1
			case 0x676C79662E2E2E31: {
				fnt::glyph g = {};
				if (readGlyph(&g, &c->children[ic], dim) != 0) {
					return -1;
				}
				fdata->glyphs.push_back(g);
			} break;
		}
	}
	if (fdata->glyphs.size() == 0) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("glfs...1 contained no glyphs :(\n");
		return -1;
	}
	if (c->data.size() != 8) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Invalid 'glfs...1' chunk size\n");
		return -1;
	}
	fdata->currentGlyph = byte::be::readu32(c->data.data()+4);
	if (fdata->currentGlyph >= fdata->glyphs.size()) {
		dbg::log("\"" + std::string(filename) + "\" - ");
		dbg::log("Invalid 'glfs...1' currentGlyph\n");
		return -1;
	}

	return 0;
}

int fnt::saveFile(
	const char* filename,
	fnt::fontData* fdata, fnt::canvasData* cdata
) {
	yak::file file {};

	// Diego...
	file.claimer = 0x446965676F2E2E2E;
	// Font....
	file.identif = 0x466F6E742E2E2E2E;

	// font...1
	file.c.id = 0x666F6E742E2E2E31;
	str::writeUTF8(&file.c.data, fdata->name);

	// cnvs...1
	yak::chunk c = {};
	c.id = 0x636E76732E2E2E31;
	c.data = std::vector<uint8_t>(10);
	byte::be::writeu16(c.data.data(),    cdata->unscaledDim[0]);
	byte::be::writeu16(c.data.data()+2,  cdata->unscaledDim[1]);
	byte::be::writeu16(c.data.data()+4,  cdata->ascender);
	byte::be::writeu16(c.data.data()+6,  cdata->descender);
	byte::be::writeu16(c.data.data()+8,  cdata->lineGap);
	file.c.children.push_back(c);

	// glfs...1
	c = (yak::chunk){};
	c.id = 0x676C66732E2E2E31;
	c.data = std::vector<uint8_t>(8);
	byte::be::writeu32(c.data.data(),   fdata->glyphs.size());
	byte::be::writeu32(c.data.data()+4, fdata->currentGlyph);
	// glyf...1
	for (size_t g = 0; g < fdata->glyphs.size(); ++g) {
		c.children.push_back(fnt::writeGlyph(&fdata->glyphs[g]));
	}
	file.c.children.push_back(c);

	if (writeFile(filename, &file) != 0) {
		return -1;
	}
	return 0;
}