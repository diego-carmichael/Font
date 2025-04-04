#include "create/logic/action.hpp"

namespace cr {
	std::string actionStr(actionSet set, action ac) {
		switch (set) {
			default: return "Unknown"; break;

			case actionSetCanvas: {
				switch (ac) {
					default: return "Canvas unknown"; break;
					case actionCanvasIdle: return "Canvas idle"; break;
					case actionCanvasResizing: return "Canvas resizing"; break;
					case actionCanvasMoving: return "Canvas moving"; break;
				}
			} break;

			case actionSetEdit: {
				switch (ac) {
					default: return "Edit unknown"; break;
					case actionEditIdle: return "Edit idle"; break;
					case actionCanvasMoving: return "Edit moving"; break;
					case actionEditMovingPoints: return "Edit moving points"; break;
				}
			} break;
		}
	}
}