#include "create/canvas/canvas.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"

cr::cv::canvasSection::canvasSection(gfx::surface* sf, gfx::rect coverage)
: sf(sf), bg(0)
{
	this->bg = new cr::cv::bg::background(sf, coverage);
	this->grid = new cr::cv::gr::grid(sf, coverage);
	this->coverage = coverage;
}

cr::cv::canvasSection::~canvasSection(void) {
	delete this->grid;
	delete this->bg;
}

void cr::cv::canvasSection::changeCoverage(gfx::rect newCoverage) {
	this->coverage = newCoverage;
	this->bg->changeCoverage(newCoverage);
	this->grid->changeCoverage(newCoverage);
}

void cr::cv::canvasSection::render(void) {
	this->bg->render(this->bg);
	this->grid->render();
}
