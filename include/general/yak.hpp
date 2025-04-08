#pragma once

#include <vector>
#include <cstdint>

namespace yak {
	typedef struct chunk chunk;
	struct chunk {
		uint64_t id;
		std::vector<uint8_t> data;
		std::vector<chunk> children;
	};

	typedef struct file file;
	struct file {
		chunk c;
		uint64_t claimer;
		uint64_t identif;
	};

	int readFile(const char* filename, file* f);
	int writeFile(const char* filename, file* f);

	chunk* findChunk(chunk* c, uint64_t id, uint32_t* ci);
}