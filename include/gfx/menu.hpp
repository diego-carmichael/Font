#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace gfx {
	typedef uint8_t menuType;
	extern const menuType menuUnknown;
	extern const menuType menuButton;

	typedef struct menu menu;
	struct menu {
		menuType type;
		std::string title;
		void* data;
		void (*onClick)(void*); // If subMenus has any elements, this doesn't apply
		std::vector<menu> subMenus;
	};
}