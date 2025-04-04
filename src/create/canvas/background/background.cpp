#include "create/canvas/background/background.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"
#include "create/logic/action.hpp"

#include <cmath>

cr::cv::bg::background::background(gfx::surface* sf, gfx::rect coverage, ib::infoBox* box) {
	this->sf = sf;
	this->coverage = coverage;
	this->box = box;

	this->mousePressListener = sf->onMousePress.addListener(
		(void*)this, cr::cv::bg::mousePress
	);
	this->mouseReleaseListener = sf->onMouseRelease.addListener(
		(void*)this, cr::cv::bg::mouseRelease
	);
	this->cursorMoveListener = sf->onCursorMove.addListener(
		(void*)this, cr::cv::bg::cursorMove
	);
	this->cursorScrollListener = sf->onCursorScroll.addListener(
		(void*)this, cr::cv::bg::cursorScroll
	);
}

cr::cv::bg::background::~background(void) {
	sf->onCursorScroll.removeListener(this->cursorScrollListener);
	sf->onCursorMove.removeListener(this->cursorMoveListener);
	sf->onMouseRelease.removeListener(this->mouseReleaseListener);
	sf->onMousePress.removeListener(this->mousePressListener);
}

void cr::cv::bg::background::render(cr::cv::bg::background* bg) {
	bg->sf->renderRect(bg->coverage, { 0.2f, 0.2f, 0.2f, 1.f });
	gfx::rect canvasRect = fnt::currentFont.cv.getScaled(bg->coverage);
	canvasRect.h -= 1.f; // To avoid lines appearing because of metrics
	bg->sf->renderRect(canvasRect, { 1.f, 1.f, 1.f, 1.f });
}

void cr::cv::bg::background::changeCoverage(gfx::rect coverage) {
	this->coverage = coverage;
}

void cr::cv::bg::mousePress(ev::listener* l, void* data) {
	if (
		fnt::currentFont.action != 0
	) {
		return;
	}

	cr::cv::bg::background* bg = (cr::cv::bg::background*)l->data;
	gfx::inp::mouseButton button = static_cast<gfx::inp::mouseButton>((size_t)data);
	if (
		button == gfx::inp::mouseLeft &&
		bg->sf->isKeyDown(gfx::inp::keyboardLCtrl)
	) {
		fnt::currentFont.changeAction(fnt::currentFont.actionSet, cr::actionCanvasMoving);
		bg->sf->getMousePos(&bg->lastCursorPos[0], &bg->lastCursorPos[1]);
	}
}

void cr::cv::bg::mouseRelease(ev::listener* l, void* data) {
	if (
		fnt::currentFont.action == 2
	) {
		fnt::currentFont.changeAction(fnt::currentFont.actionSet, cr::actionCanvasIdle);
	}
}

void cr::cv::bg::cursorMove(ev::listener* l, void* data) {
	if (
		fnt::currentFont.action != 2
	) {
		return;
	}

	cr::cv::bg::background* bg = (cr::cv::bg::background*)l->data;
	float* pos = (float*)data;
	fnt::currentFont.cv.moveScaled(
		pos[0] - bg->lastCursorPos[0],
		pos[1] - bg->lastCursorPos[1]
	);
	bg->lastCursorPos[0] = pos[0];
	bg->lastCursorPos[1] = pos[1];
}

void cr::cv::bg::cursorScroll(ev::listener* l, void* data) {
	if (
		fnt::currentFont.action != 0
	) {
		return;
	}

	cr::cv::bg::background* bg = (cr::cv::bg::background*)l->data;
	if (!bg->sf->isKeyDown(gfx::inp::keyboardLCtrl)) {
		return;
	}

	float scrollVal = (*((float*)data)) * .1f;
	float mousePos[2];
	bg->sf->getMousePos(&mousePos[0], &mousePos[1]);
	fnt::currentFont.cv.rescaleAroundPoint(
		fnt::currentFont.cv.scale + (scrollVal * fnt::currentFont.cv.scale),
		bg->coverage, mousePos[0], mousePos[1]
	);

	float num = roundf(fnt::currentFont.cv.scale * 1000.f);
	std::wstring snum = std::to_wstring((int)num);
	snum.insert(snum.end()-1, L'.');
	bg->box->setText(snum + L"%");
}