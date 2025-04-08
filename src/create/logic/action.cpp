#include "create/logic/action.hpp"

namespace cr {
	std::string actionStr(actionState state) {
		std::string s = "";
		switch (state.set) {
			default: s += "Unknown"; break;

			case actionSetCanvas: {
				switch (state.ac) {
					default: s += "Canvas unknown"; break;
					case actionCanvasIdle: s += "Canvas idle"; break;
						case actionCanvasMoving: s += "Canvas moving"; break;
					case actionCanvasResizing: s += "Canvas resizing"; break;
				}
			} break;

			case actionSetGlyph: {
				switch (state.ac) {
					default: s += "Glyph unknown"; break;
					case actionGlyphIdle: s += "Glyph idle"; break;
					case actionGlyphMoving: s += "Glyph moving"; break;
					case actionGlyphMovingPoint: s += "Glyph moving point(s)"; break;
				}
			} break;
		}

		if (state.idle) {
			s += " (idle)";
		} else {
			s += " (non-idle)";
		}
		return s;
	}
}