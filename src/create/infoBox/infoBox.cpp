#include "create/infoBox/infoBox.hpp"

#include "dbg/log.hpp"

namespace cr {
	namespace ib {
		infoBox::infoBox(gfx::surface* sf, gfx::font font) {
			this->sf = sf;
			this->font = font;
		}

		infoBox::~infoBox(void) {

		}

		void infoBox::render(void) {
			/*std::wstring str = "Test text";
			gfx::rect bound = { 50.f, 50.f, 100.f, 100.f };*/
			/*sf->renderText(
				&this->font, L"Test text",
				{ 50.f, 50.f, 100.f, 100.f },
				{ 1.f, 1.f, 1.f, 1.f }
			);*/
		}
	}
}