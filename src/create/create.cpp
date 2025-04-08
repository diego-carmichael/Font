#include "create/create.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"
#include "os/time.hpp"

cr::creationScene::creationScene(gfx::surface* sf)
: sf(sf),
	canvas(0),
	infoBox(0)
{
	this->defaultFont = sf->loadFont(sf->getDefaultFont(), 9.f);

	this->handleMenu();
	sf->setName("Font - " + fnt::currentFont.data.name);

	this->history = new cr::hst::history(sf);
	this->infoBox = new cr::ib::infoBox(sf, this->defaultFont);
	this->rcMenu = new cr::rc::rcMenu(sf, (void*)this);
	this->determineCoverage();

	this->resizeListener = sf->onResize.addListener(
		(void*)this, cr::resize
	);
	this->renderListener = sf->onRender.addListener(
		(void*)this, cr::render
	);
	this->canvasChangeListener = fnt::currentFont.cv.onCanvasChange.addListener(
		(void*)this, cr::canvasChange
	);
	this->fontOpenListener = fnt::onFontOpen.addListener(
		(void*)this, cr::fontOpen
	);
	this->fontCloseListener = fnt::onFontClose.addListener(
		(void*)this, cr::fontClose
	);
}

cr::creationScene::~creationScene(void) {
	os::closeTimers();
	fnt::onFontClose.removeListener(this->fontCloseListener);
	fnt::onFontOpen.removeListener(this->fontOpenListener);
	fnt::currentFont.cv.onCanvasChange.removeListener(this->canvasChangeListener);
	this->sf->onRender.removeListener(this->renderListener);
	this->sf->onResize.removeListener(this->resizeListener);
	delete this->canvas;
	delete this->rcMenu;
	delete this->infoBox;
	delete this->history;
	this->sf->deloadFont(&this->defaultFont);
}

void cr::creationScene::determineCoverage(void) {
	uint32_t w, h;
	sf->getDimensions(&w, &h);
	float fw = (float)w, fh = (float)h;
	gfx::rect coverage;

	coverage.x = fw / 2.f;
	coverage.y = fh / 2.f;
	coverage.w = fw;
	coverage.h = fh;
	if (!this->canvas) {
		this->canvas = new cr::cv::canvasSection(sf, coverage, this->infoBox);
	} else {
		this->canvas->changeCoverage(coverage);
	}
}

void cr::creationScene::handleMenu(void) {
	std::vector<gfx::menu> menu = std::vector<gfx::menu>(1);

	menu[0].type = gfx::menuButton;
	menu[0].title = "File";
	menu[0].subMenus = std::vector<gfx::menu>(2);
		menu[0].subMenus[0].type = gfx::menuButton;
			menu[0].subMenus[0].title = "Save";
			menu[0].subMenus[0].data = this->sf;
			menu[0].subMenus[0].onClick = fnt::saveFontButton;
			menu[0].subMenus[0].subMenus = std::vector<gfx::menu>(0);
		menu[0].subMenus[1].type = gfx::menuButton;
			menu[0].subMenus[1].title = "Open";
			menu[0].subMenus[1].data = this->sf;
			menu[0].subMenus[1].onClick = fnt::openFontButton;
			menu[0].subMenus[1].subMenus = std::vector<gfx::menu>(0);

	this->sf->setMenu(menu);
}

void cr::resize(ev::listener* l, void* data) {
	cr::creationScene* scene = (cr::creationScene*)l->data;
	scene->determineCoverage();
}

void cr::render(ev::listener* l, void* data) {
	cr::creationScene* scene = (cr::creationScene*)l->data;
	scene->canvas->render();
	scene->infoBox->render();
}

void cr::canvasChange(ev::listener* l, void* data) {
	cr::creationScene* scene = (cr::creationScene*)l->data;
	scene->sf->flagRender();
}

void cr::fontOpen(ev::listener* l, void* data) {
	cr::creationScene* scene = (cr::creationScene*)l->data;
	scene->sf->flagRender();
}

void cr::fontClose(ev::listener* l, void* data) {
	cr::creationScene* scene = (cr::creationScene*)l->data;
	scene->sf->flagRender();
}