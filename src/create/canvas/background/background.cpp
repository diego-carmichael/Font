#include "create/canvas/background/background.hpp"

#include "dbg/log.hpp"
#include "create/logic/font.hpp"
#include "create/logic/action.hpp"

cr::cv::bg::background::background(gfx::surface* sf, gfx::rect coverage) {
	this->sf = sf;
	this->coverage = coverage;

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
	bg->sf->renderRect(canvasRect, { 1.f, 1.f, 1.f, 1.f });
}

void cr::cv::bg::background::changeCoverage(gfx::rect coverage) {
	this->coverage = coverage;
}

void cr::cv::bg::mousePress(ev::listener* l, void* data) {
	if (
		fnt::currentFont.actionSet != cr::actionSetCanvas ||
		fnt::currentFont.action != cr::actionCanvasIdle
	) {
		return;
	}

	cr::cv::bg::background* bg = (cr::cv::bg::background*)l->data;
	gfx::inp::mouseButton button = static_cast<gfx::inp::mouseButton>((size_t)data);
	if (
		button == gfx::inp::mouseLeft &&
		bg->sf->isKeyDown(gfx::inp::keyboardLCtrl)
	) {
		dbg::log("[ACTION] Moving canvas...\n");
		fnt::currentFont.action = cr::actionCanvasMoving;
		bg->sf->getMousePos(&bg->lastCursorPos[0], &bg->lastCursorPos[1]);
	}
}

void cr::cv::bg::mouseRelease(ev::listener* l, void* data) {
	if (
		fnt::currentFont.actionSet == cr::actionSetCanvas &&
		fnt::currentFont.action == cr::actionCanvasMoving
	) {
		dbg::log("[ACTION] Moved canvas\n");
		fnt::currentFont.action = cr::actionCanvasIdle;
	}
}

void cr::cv::bg::cursorMove(ev::listener* l, void* data) {
	if (
		fnt::currentFont.actionSet != cr::actionSetCanvas ||
		fnt::currentFont.action != cr::actionCanvasMoving
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
		fnt::currentFont.actionSet != cr::actionSetCanvas ||
		fnt::currentFont.action != cr::actionCanvasIdle
	) {
		return;
	}

	cr::cv::bg::background* bg = (cr::cv::bg::background*)l->data;
	float scrollVal = (*((float*)data)) * .1f;
	float mousePos[2];
	bg->sf->getMousePos(&mousePos[0], &mousePos[1]);
	fnt::currentFont.cv.rescaleAroundPoint(
		fnt::currentFont.cv.scale + (scrollVal * fnt::currentFont.cv.scale),
		bg->coverage, mousePos[0], mousePos[1]
	);
}