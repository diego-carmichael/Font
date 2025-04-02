#include "create/rcMenu/rcMenu.hpp"

#include "create/logic/font.hpp"
#include "dbg/log.hpp"

namespace cr {
	namespace rc {
		rcMenu::rcMenu(gfx::surface* sf) {
			this->sf = sf;

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

			switch (fnt::currentFont.actionSet) {
				default: dbg::log("Unprocessed action set! Bad!\n"); break;

				case cr::actionSetCanvas: {
					// ...
				} break;

				case cr::actionSetEdit: {
					// ...
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
				if (fnt::currentFont.actionSet == cr::actionSetCanvas) {
					submenu.type = gfx::menuSelected;
				} else {
					submenu.type = gfx::menuUnselected;
				}
				actionSetMenu.subMenus.push_back(submenu);

				submenu.title = "Glyph";
				submenu.onClick = changeToEdit;
				if (fnt::currentFont.actionSet == cr::actionSetEdit) {
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
			fnt::currentFont.changeAction(cr::actionSetCanvas, cr::actionCanvasIdle);
			rcMenu* menu = (rcMenu*)data;
			menu->process();
		}

		void changeToEdit(void* data) {
			fnt::currentFont.changeAction(cr::actionSetEdit, cr::actionEditIdle);
			rcMenu* menu = (rcMenu*)data;
			menu->process();
		}
	}
}