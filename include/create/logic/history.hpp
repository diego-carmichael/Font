#pragma once

#include "create/logic/font.hpp"
#include "general/event.hpp"

#include <cstdint>
#include <string>

namespace cr {
	namespace hst {
		typedef uint16_t eventType;
		const eventType eventUnknown = 0;

		const eventType eventPointsMove = 1;
		typedef struct pointMoveData pointMoveData;
		struct pointMoveData {
			size_t pointsMoved;
			// If pointsMoved == 1:
				uint32_t prevPos[2];
				uint32_t newPos[2];
			// Else:
				int32_t offset[2];
		};
		std::string pointMoveOccurString(pointMoveData* data);
		std::string pointMoveUndoString(pointMoveData* data);
		std::string pointMoveRedoString(pointMoveData* data);

		// Could be a union, but vector :(
		typedef struct eventData eventData;
		struct eventData {
			pointMoveData pointMove;
		};
		std::string eventOccurString(eventType type, eventData* data);
		std::string eventUndoString(eventType type, eventData* data);
		std::string eventRedoString(eventType type, eventData* data);

		typedef struct event event;
		struct event {
			eventType type;
			eventData data;
			fnt::fontData prevFont;
			fnt::canvasData prevCanvas;
			fnt::fontData newFont;
			fnt::canvasData newCanvas;
		};

		// Note: this vector should not be read directly from for data!
		// Its data can be misleading; read history.cpp to see it
		extern std::vector<event> events;
		void clearEvents(void);
		void addEvent(event* ev);
		int undoEvent(void); // Non-zero if there's no events to undo
		int redoEvent(void); // Non-zero if there's no events to redo

		extern ev::event onEventsClear; // (0)
		extern ev::event onEventAdd; // (event*)
		extern ev::event onEventUndo; // (event*)
		extern ev::event onEventRedo; // (event*)
	}
}