// This is an amazing file, don't worry about it
#include "create/logic/history.hpp"

#include "dbg/log.hpp"

namespace cr {
	namespace hst {
		std::string pointMoveOccurString(pointMoveData* data) {
			if (data->pointsMoved == 1) {
				return "Moved point from ("
					+ std::to_string(data->prevPos[0]) + ", "
					+ std::to_string(data->prevPos[1]) + ") to ("
					+ std::to_string(data->newPos[0])  + ", "
					+ std::to_string(data->newPos[1])  + ")"
				;
			}
			else {
				return "Moved "
					+ std::to_string(data->pointsMoved) + " points by ("
					+ std::to_string(data->offset[0])   + ", "
					+ std::to_string(data->offset[1])   + ")"
				;
			}
		}

		std::string pointMoveUndoString(pointMoveData* data) {
			if (data->pointsMoved == 1) {
				return "Undo moving point from ("
					+ std::to_string(data->newPos[0])  + ", "
					+ std::to_string(data->newPos[1])  + ") back to ("
					+ std::to_string(data->prevPos[0]) + ", "
					+ std::to_string(data->prevPos[1]) + ")"
				;
			}
			else {
				return "Undo moving "
					+ std::to_string(data->pointsMoved) + " points by ("
					+ std::to_string(data->offset[0])   + ", "
					+ std::to_string(data->offset[1])   + ")"
				;
			}
		}

		std::string pointMoveRedoString(pointMoveData* data) {
			if (data->pointsMoved == 1) {
				return "Redo moving point from ("
					+ std::to_string(data->prevPos[0]) + ", "
					+ std::to_string(data->prevPos[1]) + ") to ("
					+ std::to_string(data->newPos[0])  + ", "
					+ std::to_string(data->newPos[1]) + ")"
				;
			}
			else {
				return "Redo moving "
					+ std::to_string(data->pointsMoved) + " points by ("
					+ std::to_string(data->offset[0])   + ", "
					+ std::to_string(data->offset[1])   + ")"
				;
			}
		}

		std::string pointAddOccurString(pointAddData* data) {
			if (data->pointsAdded == 1) {
				return "Added point at ("
					+ std::to_string(data->pos[0]) + ", "
					+ std::to_string(data->pos[1]) + ")"
				;
			}
			else {
				return "Added " + std::to_string(data->pointsAdded) + " points";
			}
		}

		std::string pointAddUndoString(pointAddData* data) {
			if (data->pointsAdded == 1) {
				return "Undo adding point at ("
					+ std::to_string(data->pos[0]) + ", "
					+ std::to_string(data->pos[1]) + ")"
				;
			}
			else {
				return "Undo adding " + std::to_string(data->pointsAdded) + " points";
			}
		}

		std::string pointAddRedoString(pointAddData* data) {
			if (data->pointsAdded == 1) {
				return "Redo adding point at ("
					+ std::to_string(data->pos[0]) + ", "
					+ std::to_string(data->pos[1]) + ")"
				;
			}
			else {
				return "Redo adding " + std::to_string(data->pointsAdded) + " points";
			}
		}

		std::string pointRemoveOccurString(pointRemoveData* data) {
			if (data->pointsRemoved == 1) {
				return "Removed point at ("
					+ std::to_string(data->pos[0]) + ", "
					+ std::to_string(data->pos[1]) + ")"
				;
			}
			else {
				return "Removed " + std::to_string(data->pointsRemoved) + " points";
			}
		}

		std::string pointRemoveUndoString(pointRemoveData* data) {
			if (data->pointsRemoved == 1) {
				return "Undo removing point at ("
					+ std::to_string(data->pos[0]) + ", "
					+ std::to_string(data->pos[1]) + ")"
				;
			}
			else {
				return "Undo removing " + std::to_string(data->pointsRemoved) + " points";
			}
		}

		std::string pointRemoveRedoString(pointRemoveData* data) {
			if (data->pointsRemoved == 1) {
				return "Redo removing point at ("
					+ std::to_string(data->pos[0]) + ", "
					+ std::to_string(data->pos[1]) + ")"
				;
			}
			else {
				return "Redo removing " + std::to_string(data->pointsRemoved) + " points";
			}
		}

		std::string pointSwitchOccurString(pointSwitchData* data) {
			std::string s = "";
			if (data->pointsSwitched == 1) {
				s += "Point switched from ";
				if (data->on) {
					s += "off to on ";
				} else {
					s += "on to off ";
				}
				s += "at (";
				s += std::to_string(data->pos[0]) + ", ";
				s += std::to_string(data->pos[1]) + ")";
			}
			else {
				s += std::to_string(data->pointsSwitched);
				s += " points switched ";
				if (data->on) {
					s += "on";
				} else {
					s += "off";
				}
			}
			return s;
		}

		std::string pointSwitchUndoString(pointSwitchData* data) {
			std::string s = "Undo ";
			if (data->pointsSwitched == 1) {
				s += "point switching ";
				if (data->on) {
					s += "on (back to off) ";
				} else {
					s += "off (back to on) ";
				}
				s += "at (";
				s += std::to_string(data->pos[0]) + ", ";
				s += std::to_string(data->pos[1]) + ")";
			}
			else {
				s += std::to_string(data->pointsSwitched);
				s += " points switched ";
				if (data->on) {
					s += "on";
				} else {
					s += "off";
				}
			}
			return s;
		}

		std::string pointSwitchRedoString(pointSwitchData* data) {
			std::string s = "Redo ";
			if (data->pointsSwitched == 1) {
				s += "point switching ";
				if (data->on) {
					s += "off to on ";
				} else {
					s += "on to off ";
				}
				s += "at (";
				s += std::to_string(data->pos[0]) + ", ";
				s += std::to_string(data->pos[1]) + ")";
			}
			else {
				s += std::to_string(data->pointsSwitched);
				s += " points switched ";
				if (data->on) {
					s += "on";
				} else {
					s += "off";
				}
			}
			return s;
		}

		std::string contourSwitchOccurString(contourSwitchData* data) {
			std::string s = "Switched " + std::to_string(data->contoursSwitched);
			if (data->contoursSwitched == 1) {
				s += " contour ";
			} else {
				s += " contours ";
			}
			if (data->in) {
				s += "inside";
			} else {
				s += "outside";
			}
			return s;
		}

		std::string contourSwitchUndoString(contourSwitchData* data) {
			std::string s = "Undo switching " + std::to_string(data->contoursSwitched);
			if (data->contoursSwitched == 1) {
				s += " contour ";
			} else {
				s += " contours ";
			}
			if (data->in) {
				s += "inside";
			} else {
				s += "outside";
			}
			return s;
		}

		std::string contourSwitchRedoString(contourSwitchData* data) {
			std::string s = "Redo switching " + std::to_string(data->contoursSwitched);
			if (data->contoursSwitched == 1) {
				s += " contour ";
			} else {
				s += " contours ";
			}
			if (data->in) {
				s += "inside";
			} else {
				s += "outside";
			}
			return s;
		}

		std::string eventOccurString(eventType type, eventData* data) {
			switch (type) {
				default: return "Unknown event type for occur! Weird!"; break;
				case eventPointsMove: return pointMoveOccurString(&data->pointMove); break;
				case eventPointsAdd: return pointAddOccurString(&data->pointAdd); break;
				case eventPointsRemove: return pointRemoveOccurString(&data->pointRemove); break;
				case eventPointsSwitch: return pointSwitchOccurString(&data->pointSwitch); break;
				case eventContourSwitch: return contourSwitchOccurString(&data->contourSwitch); break;
			}
		}

		std::string eventUndoString(eventType type, eventData* data) {
			switch (type) {
				default: return "Unknown event type for undo! Weird!"; break;
				case eventPointsMove: return pointMoveUndoString(&data->pointMove); break;
				case eventPointsAdd: return pointAddUndoString(&data->pointAdd); break;
				case eventPointsRemove: return pointRemoveUndoString(&data->pointRemove); break;
				case eventPointsSwitch: return pointSwitchUndoString(&data->pointSwitch); break;
				case eventContourSwitch: return contourSwitchUndoString(&data->contourSwitch); break;
			}
		}

		std::string eventRedoString(eventType type, eventData* data) {
			switch (type) {
				default: return "Unknown event type for redo! Weird!"; break;
				case eventPointsMove: return pointMoveRedoString(&data->pointMove); break;
				case eventPointsAdd: return pointAddRedoString(&data->pointAdd); break;
				case eventPointsRemove: return pointRemoveRedoString(&data->pointRemove); break;
				case eventPointsSwitch: return pointSwitchRedoString(&data->pointSwitch); break;
				case eventContourSwitch: return contourSwitchRedoString(&data->contourSwitch); break;
			}
		}

		std::vector<event> events = std::vector<event>(0);
		size_t currentEvent = 0; // Index is actually +1, so 0 means no event

		ev::event onEventsClear {};
		void clearEvents(void) {
			events = std::vector<event>(0);
			currentEvent = 0;
			onEventsClear.call(0);
		}

		ev::event onEventAdd {};
		void addEvent(event* ev) {
			if (currentEvent == events.size()) {
				events.push_back(*ev);
				currentEvent += 1;
			}
			else {
				events.erase(events.begin() + currentEvent, events.end());
				events.push_back(*ev);
				currentEvent = events.size();
			}
			onEventAdd.call((void*)ev);
		}

		ev::event onEventUndo {};
		int undoEvent(void) {
			if (currentEvent == 0) {
				return 1;
			}

			currentEvent -= 1;
			fnt::currentFont.data = events[currentEvent].prevFont;
			fnt::currentFont.cv.data = events[currentEvent].prevCanvas;
			onEventUndo.call((void*)&events[currentEvent]);
			return 0;
		}

		ev::event onEventRedo {};
		int redoEvent(void) {
			if (currentEvent == events.size()) {
				return 1;
			}

			fnt::currentFont.data = events[currentEvent].newFont;
			fnt::currentFont.cv.data = events[currentEvent].newCanvas;
			onEventRedo.call((void*)&events[currentEvent]);
			currentEvent += 1;
			return 0;
		}
	}
}