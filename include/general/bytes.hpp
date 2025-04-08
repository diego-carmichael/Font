#pragma once

#include <cstdint>

namespace byte {
	namespace le {
		int8_t   reads8   (uint8_t* b);
		void     writes8  (uint8_t* b, int8_t i);
		uint16_t readu16  (uint8_t* b);
		void     writeu16 (uint8_t* b, uint16_t i);
		int16_t  reads16  (uint8_t* b);
		void     writes16 (uint8_t* b, int16_t i);
		uint32_t readu32  (uint8_t* b);
		void     writeu32 (uint8_t* b, uint32_t i);
		int32_t  reads32  (uint8_t* b);
		void     writes32 (uint8_t* b, int32_t i);
		uint64_t readu64  (uint8_t* b);
		void     writeu64 (uint8_t* b, uint64_t i);
		int64_t  reads64  (uint8_t* b);
		void     writes64 (uint8_t* b, int64_t i);
	}
	namespace be {
		int8_t   reads8   (uint8_t* b);
		void     writes8  (uint8_t* b, int8_t i);
		uint16_t readu16  (uint8_t* b);
		void     writeu16 (uint8_t* b, uint16_t i);
		int16_t  reads16  (uint8_t* b);
		void     writes16 (uint8_t* b, int16_t i);
		uint32_t readu32  (uint8_t* b);
		void     writeu32 (uint8_t* b, uint32_t i);
		int32_t  reads32  (uint8_t* b);
		void     writes32 (uint8_t* b, int32_t i);
		uint64_t readu64  (uint8_t* b);
		void     writeu64 (uint8_t* b, uint64_t i);
		int64_t  reads64  (uint8_t* b);
		void     writes64 (uint8_t* b, int64_t i);
	}
}