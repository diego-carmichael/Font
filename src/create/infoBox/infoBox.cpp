#include "create/infoBox/infoBox.hpp"

#include "dbg/log.hpp"
#include "os/time.hpp"

namespace cr {
	namespace ib {
		infoBox::infoBox(gfx::surface* sf, gfx::font font) {
			this->sf = sf;
			this->font = font;

			this->displayTime = 2.f;
			this->text = L"...";
			this->shouldRender = false;

			this->cursorMoveListener = sf->onCursorMove.addListener(
				(void*)this, cursorMove
			);
			this->rightClickMenuAppearListener = 
			sf->onRightClickMenuAppearing.addListener(
				(void*)this, rightClickMenuAppear
			);
		}

		infoBox::~infoBox(void) {
			sf->onRightClickMenuAppearing.removeListener(
				this->rightClickMenuAppearListener
			);
			sf->onCursorMove.removeListener(this->cursorMoveListener);
		}

		void infoBox::render(void) {
			if (!this->shouldRender) {
				return;
			}

			gfx::rect bound;
			sf->renderText(
				&this->font, this->text,
				{ 0.f, 0.f, 100.f, 10000.f },
				{ 1.f, 1.f, 1.f, 1.f },
				&bound
			);

			gfx::rect rect;
			this->sf->getMousePos(&rect.x, &rect.y);
			rect.x += 10.f;
			rect.y += 10.f;
			rect.w = bound.w;
			rect.h = bound.h;
			rect.x += rect.w / 2.f;
			rect.y += rect.h / 2.f;
			this->sf->renderRect(rect, { 0.f, 0.f, 0.f, 1.f });

			this->sf->renderText(
				&this->font, this->text,
				rect, { 1.f, 1.f, 1.f, 1.f }, 0
			);
		}

		void infoBox::setText(std::wstring s) {
			this->text = s;
			this->sf->flagRender();
			this->shouldRender = true;

			os::timer(
				(os::timeSec)this->displayTime,
				cr::ib::resetText,
				(void*)this, false
			);
		}

		void resetText(void* data) {
			infoBox* box = (infoBox*)data;
			box->shouldRender = false;
			box->sf->flagRender();
		}

		void cursorMove(ev::listener* l, void* data) {
			infoBox* box = (infoBox*)l->data;
			if (box->shouldRender) {
				box->sf->flagRender();
			}
		}

		void rightClickMenuAppear(ev::listener* l, void* data) {
			infoBox* box = (infoBox*)l->data;
			box->shouldRender = false;
			box->sf->flagRender();
		}
	}
}