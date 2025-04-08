#include "general/bytes.hpp"

// The functions for signed values here definitely aren't implemented
// the way you're supposed to. It's fine, probably. Hopefully.

// This file is generally quite horrid. But it works for my purposes.

namespace byte {
	namespace le {
		int8_t reads8 (uint8_t* b) {
			return *(int8_t*)b;
		}

		void writes8 (uint8_t* b, int8_t i) {
			((int8_t*)(b))[0] = i;
		}

		uint16_t readu16 (uint8_t* b) {
			return (
				(((uint16_t)b[0]) << 0)  |
				(((uint16_t)b[1]) << 8)
			);
		}

		void writeu16 (uint8_t* b, uint16_t i) {
			b[0] = (uint8_t)(i >> 0);
			b[1] = (uint8_t)(i >> 8);
		}

		int16_t reads16 (uint8_t* b) {
			uint16_t u = byte::le::readu16(b);
			return *(int16_t*)&u;
		}

		void writes16 (uint8_t* b, int16_t i) {
			uint16_t un = *(uint16_t*)&i;
			b[0] = (uint8_t)(i >> 0);
			b[1] = (uint8_t)(i >> 8);
		}

		uint32_t readu32 (uint8_t* b) {
			return (
				(((uint32_t)b[0]) << 0)  |
				(((uint32_t)b[1]) << 8)  |
				(((uint32_t)b[2]) << 16) |
				(((uint32_t)b[3]) << 24)
			);
		}

		void writeu32 (uint8_t* b, uint32_t i) {
			b[0] = (uint8_t)(i >> 0);
			b[1] = (uint8_t)(i >> 8);
			b[2] = (uint8_t)(i >> 16);
			b[3] = (uint8_t)(i >> 24);
		}

		int32_t reads32 (uint8_t* b) {
			uint32_t u = byte::le::readu32(b);
			return *(int32_t*)&u;
		}

		void writes32 (uint8_t* b, int32_t i) {
			uint32_t un = *(uint32_t*)&i;
			b[0] = (uint8_t)(un >> 0);
			b[1] = (uint8_t)(un >> 8);
			b[2] = (uint8_t)(un >> 16);
			b[3] = (uint8_t)(un >> 24);
		}

		uint64_t readu64 (uint8_t* b) {
			return (
				(((uint64_t)b[0]) << 0)  |
				(((uint64_t)b[1]) << 8)  |
				(((uint64_t)b[2]) << 16) |
				(((uint64_t)b[3]) << 24) |
				(((uint64_t)b[4]) << 32) |
				(((uint64_t)b[5]) << 40) |
				(((uint64_t)b[6]) << 48) |
				(((uint64_t)b[7]) << 56)
			);
		}

		void writeu64 (uint8_t* b, uint64_t i) {
			b[0] = (uint8_t)(i >> 0);
			b[1] = (uint8_t)(i >> 8);
			b[2] = (uint8_t)(i >> 16);
			b[3] = (uint8_t)(i >> 24);
			b[4] = (uint8_t)(i >> 32);
			b[5] = (uint8_t)(i >> 40);
			b[6] = (uint8_t)(i >> 48);
			b[7] = (uint8_t)(i >> 56);
		}

		int64_t reads64 (uint8_t* b) {
			uint64_t u = byte::le::readu64(b);
			return *(int64_t*)&u;
		}

		void writes64 (uint8_t* b, int64_t i) {
			uint64_t un = *(uint64_t*)&i;
			b[0] = (uint8_t)(un >> 0);
			b[1] = (uint8_t)(un >> 8);
			b[2] = (uint8_t)(un >> 16);
			b[3] = (uint8_t)(un >> 24);
			b[4] = (uint8_t)(un >> 32);
			b[5] = (uint8_t)(un >> 40);
			b[6] = (uint8_t)(un >> 48);
			b[7] = (uint8_t)(un >> 56);
		}
	}

	namespace be {
		int8_t reads8 (uint8_t* b) {
			return *(int8_t*)b;
		}

		void writes8 (uint8_t* b, int8_t i) {
			((int8_t*)(b))[0] = i;
		}

		uint16_t readu16 (uint8_t* b) {
			return (
				(((uint16_t)b[1]) << 0)  |
				(((uint16_t)b[0]) << 8)
			);
		}

		void writeu16 (uint8_t* b, uint16_t i) {
			b[1] = (uint8_t)(i >> 0);
			b[0] = (uint8_t)(i >> 8);
		}

		int16_t reads16 (uint8_t* b) {
			uint16_t u = byte::be::readu16(b);
			return *(int16_t*)&u;
		}

		void writes16 (uint8_t* b, int16_t i) {
			uint16_t un = *(uint16_t*)&i;
			b[1] = (uint8_t)(i >> 0);
			b[0] = (uint8_t)(i >> 8);
		}

		uint32_t readu32 (uint8_t* b) {
			return (
				(((uint32_t)b[3]) << 0)  |
				(((uint32_t)b[2]) << 8)  |
				(((uint32_t)b[1]) << 16) |
				(((uint32_t)b[0]) << 24)
			);
		}

		void writeu32 (uint8_t* b, uint32_t i) {
			b[3] = (uint8_t)(i >> 0);
			b[2] = (uint8_t)(i >> 8);
			b[1] = (uint8_t)(i >> 16);
			b[0] = (uint8_t)(i >> 24);
		}

		int32_t reads32 (uint8_t* b) {
			uint32_t u = byte::be::readu32(b);
			return *(int32_t*)&u;
		}

		void writes32 (uint8_t* b, int32_t i) {
			uint32_t un = *(uint32_t*)&i;
			b[3] = (uint8_t)(un >> 0);
			b[2] = (uint8_t)(un >> 8);
			b[1] = (uint8_t)(un >> 16);
			b[0] = (uint8_t)(un >> 24);
		}

		uint64_t readu64 (uint8_t* b) {
			return (
				(((uint64_t)b[7]) << 0)  |
				(((uint64_t)b[6]) << 8)  |
				(((uint64_t)b[5]) << 16) |
				(((uint64_t)b[4]) << 24) |
				(((uint64_t)b[3]) << 32) |
				(((uint64_t)b[2]) << 40) |
				(((uint64_t)b[1]) << 48) |
				(((uint64_t)b[0]) << 56)
			);
		}

		void writeu64 (uint8_t* b, uint64_t i) {
			b[7] = (uint8_t)(i >> 0);
			b[6] = (uint8_t)(i >> 8);
			b[5] = (uint8_t)(i >> 16);
			b[4] = (uint8_t)(i >> 24);
			b[3] = (uint8_t)(i >> 32);
			b[2] = (uint8_t)(i >> 40);
			b[1] = (uint8_t)(i >> 48);
			b[0] = (uint8_t)(i >> 56);
		}

		int64_t reads64 (uint8_t* b) {
			uint64_t u = byte::be::readu64(b);
			return *(int64_t*)&u;
		}

		void writes64 (uint8_t* b, int64_t i) {
			uint64_t un = *(uint64_t*)&i;
			b[7] = (uint8_t)(un >> 0);
			b[6] = (uint8_t)(un >> 8);
			b[5] = (uint8_t)(un >> 16);
			b[4] = (uint8_t)(un >> 24);
			b[3] = (uint8_t)(un >> 32);
			b[2] = (uint8_t)(un >> 40);
			b[1] = (uint8_t)(un >> 48);
			b[0] = (uint8_t)(un >> 56);
		}
	}
}