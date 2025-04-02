#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace gfx {
	typedef uint8_t menuType;
	const menuType menuUnknown = 0;
	const menuType menuButton = 1;
	const menuType menuSelected = 2;
	const menuType menuUnselected = 3;

	typedef struct menu menu;
	struct menu {
		menuType type;
		std::string title;
		void* data;
		void (*onClick)(void*); // If subMenus has any elements, this doesn't apply
		std::vector<menu> subMenus;
	};
}