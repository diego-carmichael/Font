#include "create/canvas/canvas.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"

cr::cv::canvasSection::canvasSection(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box)
: sf(sf), bg(0), metrics(0)
{
	this->bg = new cr::cv::bg::background(sf, coverage, box);
	this->metrics = new cr::cv::mt::metrics(sf, coverage);
	this->grid = new cr::cv::gr::grid(sf, coverage);
	this->coverage = coverage;
}

cr::cv::canvasSection::~canvasSection(void) {
	delete this->grid;
	delete this->metrics;
	delete this->bg;
}

void cr::cv::canvasSection::changeCoverage(gfx::rect newCoverage) {
	this->coverage = newCoverage;
	this->bg->changeCoverage(newCoverage);
	this->metrics->changeCoverage(newCoverage);
	this->grid->changeCoverage(newCoverage);
}

void cr::cv::canvasSection::render(void) {
	this->bg->render(this->bg);
	this->metrics->render();
	this->grid->render();
}
