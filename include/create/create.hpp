#pragma once

#include "gui/scene.hpp"
#include "create/history/history.hpp"
#include "create/canvas/canvas.hpp"
#include "general/event.hpp"
#include "create/infoBox/infoBox.hpp"
#include "create/rcMenu/rcMenu.hpp"

namespace cr {
	class creationScene : public gui::scene {
	public:
		gfx::surface* sf;
		cv::canvasSection* canvas;
		hst::history* history;
		ib::infoBox* infoBox;
		rc::rcMenu* rcMenu;
		ev::listener* resizeListener;
		ev::listener* renderListener;
		ev::listener* canvasChangeListener;
		gfx::font defaultFont;
	public:
		creationScene(gfx::surface* sf);
		~creationScene(void);

		void determineCoverage(void);
		void resize(ev::listener* l);
		void handleMenu(void);
	};

	void resize(ev::listener* l, void* data);
	void render(ev::listener* l, void* data);
	void canvasChange(ev::listener* l, void* data);
}