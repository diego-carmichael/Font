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

		std::string eventOccurString(eventType type, eventData* data) {
			switch (type) {
				default: return "Unknown event type for occur! Weird!"; break;
				case eventPointsMove: return pointMoveOccurString(&data->pointMove); break;
			}
		}

		std::string eventUndoString(eventType type, eventData* data) {
			switch (type) {
				default: return "Unknown event type for undo! Weird!"; break;
				case eventPointsMove: return pointMoveUndoString(&data->pointMove); break;
			}
		}

		std::string eventRedoString(eventType type, eventData* data) {
			switch (type) {
				default: return "Unknown event type for redo! Weird!"; break;
				case eventPointsMove: return pointMoveRedoString(&data->pointMove); break;
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