#include "create/rcMenu/rcMenu.hpp"

#include "create/logic/font.hpp"
#include "dbg/log.hpp"
#include "create/canvas/glyph/glyph.hpp"

namespace cr {
	namespace rc {
		rcMenu::rcMenu(gfx::surface* sf, void* createRef) {
			this->sf = sf;
			this->createRef = createRef;

			this->actionChangeListener = fnt::currentFont.onActionChange.addListener(
				(void*)this, actionChange
			);
			this->process();
		}

		rcMenu::~rcMenu(void) {
			fnt::currentFont.onActionChange.removeListener(
				this->actionChangeListener
			);
		}

		void rcMenu::process(void) {
			std::vector<gfx::menu> menus = std::vector<gfx::menu>(0);

			switch (fnt::currentFont.acState.set) {
				default: dbg::log("Unprocessed action set! Bad!\n"); break;

				case cr::actionSetCanvas: {
					// ...
				} break;

				case cr::actionSetGlyph: {
					gfx::menu submenu {};
					// Add point
					submenu.type = gfx::menuButton;
					submenu.title = "Add point";
					submenu.data = this->createRef;
					submenu.onClick = cr::cv::gl::onPointAdd;
					menus.push_back(submenu);
					// Remove point
					if (fnt::currentFont.acState.data.gl.selected) {
						submenu.type = gfx::menuButton;
						submenu.title = "Remove point";
						submenu.data = this->createRef;
						submenu.onClick = cr::cv::gl::onPointDelete;
						menus.push_back(submenu);
					}
					// Switch point on + off
					if (fnt::currentFont.acState.data.gl.selected) {
						submenu.type = gfx::menuButton;
						submenu.title = "Switch point on";
						submenu.data = this->createRef;
						submenu.onClick = cr::cv::gl::onPointSwitchOn;
						menus.push_back(submenu);
						submenu.type = gfx::menuButton;
						submenu.title = "Switch point off";
						submenu.data = this->createRef;
						submenu.onClick = cr::cv::gl::onPointSwitchOff;
						menus.push_back(submenu);
					}
				} break;
			}

			{
				gfx::menu actionSetMenu {};
				actionSetMenu.type = gfx::menuButton;
				actionSetMenu.title = "Edit mode";
				gfx::menu submenu {};
				submenu.data = (void*)this;

				submenu.title = "Canvas";
				submenu.onClick = changeToCanvas;
				if (fnt::currentFont.acState.set == cr::actionSetCanvas) {
					submenu.type = gfx::menuSelected;
				} else {
					submenu.type = gfx::menuUnselected;
				}
				actionSetMenu.subMenus.push_back(submenu);

				submenu.title = "Glyph";
				submenu.onClick = changeToEdit;
				if (fnt::currentFont.acState.set == cr::actionSetGlyph) {
					submenu.type = gfx::menuSelected;
				} else {
					submenu.type = gfx::menuUnselected;
				}
				actionSetMenu.subMenus.push_back(submenu);

				menus.push_back(actionSetMenu);
			}

			this->sf->setRightClickMenu(menus);
		}

		void actionChange(ev::listener* l, void* data) {
			rcMenu* menu = (rcMenu*)l->data;
			menu->process();
		}

		void changeToCanvas(void* data) {
			cr::actionState state = fnt::currentFont.acState;
			state.set = cr::actionSetCanvas;
			state.ac = 0;
			state.idle = true;
			fnt::currentFont.changeAction(state);
			rcMenu* menu = (rcMenu*)data;
			menu->process();
			menu->sf->flagRender();
		}

		void changeToEdit(void* data) {
			cr::actionState state = fnt::currentFont.acState;
			state.set = cr::actionSetGlyph;
			state.ac = 0;
			state.idle = true;
			fnt::currentFont.changeAction(state);
			rcMenu* menu = (rcMenu*)data;
			menu->process();
			menu->sf->flagRender();
		}
	}
}