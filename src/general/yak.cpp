// Note: this does not totally test for integer overflow, so this
// is totally vulnerable to stuff like attack vectors. It makes
// it more fun that way, in my opinion.
#include "general/yak.hpp"

#include "general/bytes.hpp"
#include "dbg/log.hpp"

#include <cstdio>

namespace yak {
	typedef struct readCi readCi;
	struct readCi {
		FILE* f;
		size_t i;
		size_t flen;
		uint32_t numChunks;
		uint64_t chunkDataSize;
		uint32_t pNumChunks;
		uint64_t pChunkDataSize;
	};

	int readChunk(chunk* c, readCi* ri, chunk* par) {
		*c = {};

		// Read header data
		if (ri->i + 24 >= ri->flen) {
			return -1;
		}
		uint8_t header[24];
		fseek(ri->f, ri->i, SEEK_SET);
		fread(header, 24, 1, ri->f);
		ri->i += 24;

		// Read into chunk
		c->id = byte::be::readu64(header);
		c->data = std::vector<uint8_t>(byte::be::readu64(header+8));
		uint64_t ccl = byte::be::readu64(header+16);

		// Allocate and read chunk data
		ri->pChunkDataSize += c->data.size();
		if (ri->pChunkDataSize > ri->chunkDataSize) {
			return -1;
		}
		if (ri->i + c->data.size() > ri->flen) {
			return -1;
		}
		fseek(ri->f, ri->i, SEEK_SET);
		fread(c->data.data(), c->data.size(), 1, ri->f);
		ri->i += c->data.size();

		// Read all children
		while (ccl) {
			// Allocate new child chunk
			c->children.resize(c->children.size()+1);
			ri->pNumChunks += 1;
			if (ri->pNumChunks > ri->numChunks) {
				return -1;
			}
			// Read child chunk
			size_t previ = ri->i;
			int res = readChunk(&c->children[c->children.size()-1], ri, c);
			if (res != 0) {
				return res;
			}
			if (ri->i - previ > ccl) {
				return -1;
			}
			ccl -= ri->i - previ;
		}

		return 0;
	}

	int readFile(const char* filename, file* f) {
		*f = {};

		FILE* fstd = fopen(filename, "rb");
		if (!fstd) {
			dbg::log("Read: .yak failed to open file \"" + std::string(filename) + "\"\n");
			return -1;
		}

		fseek(fstd, 0, SEEK_END);
		size_t filelen = ftell(fstd);
		if (filelen < 33) {
			fclose(fstd);
			dbg::log("Read: .yak file \"" + std::string(filename) + "\" is too small\n");
			return -1;
		}

		uint8_t begThing[33];
		fseek(fstd, 0, SEEK_SET);
		fread(begThing, 33, 1, fstd);

		readCi ri {};
		ri.f = fstd;
		ri.i = 33;
		ri.flen = filelen;
		ri.pNumChunks = 0;
		ri.pChunkDataSize = 0;

		// .yak
		if (byte::be::readu32(begThing) != 0x2E79616B) {
			fclose(fstd);
			dbg::log("Read: .yak signature failed\n");
			return -1;
		}
		// Version 1
		if (begThing[4] != 1) {
			dbg::log("Read: .yak version isn't 1, may not work!\n");
		}
		// Chunk count
		ri.numChunks = byte::be::readu32(begThing + 5);
		if (ri.numChunks == 0) {
			fclose(fstd);
			dbg::log("Read: .yak 0 chunks\n");
			return -1;
		}
		// Chunk data size
		ri.chunkDataSize = byte::be::readu64(begThing + 9);
		if (ri.chunkDataSize == 0) {
			fclose(fstd);
			dbg::log("Read: .yak chunk data size 0\n");
			return -1;
		}
		// Claimer and type
		f->claimer = byte::be::readu64(begThing + 17);
		f->identif = byte::be::readu64(begThing + 25);

		int res = readChunk(&f->c, &ri, 0);
		if (res != 0) {
			fclose(fstd);
			dbg::log("Read: .yak read chunk call failed\n");
			return -1;
		}

		fclose(fstd);
		return 0;
	}

	typedef struct writeCi writeCi;
	struct writeCi {
		FILE* f;
		size_t i;
		uint32_t chunkCount;
		uint64_t chunkSize;
	};

	int writeChunk(chunk* c, writeCi* wi) {
		// Increment vars
		size_t previ = wi->i;
		{
			uint32_t chunkCount = wi->chunkCount + 1;
			if (chunkCount < wi->chunkCount) {
				return -1;
			}

			uint64_t chunkSize = wi->chunkSize + c->data.size();
			if (chunkSize < wi->chunkSize) {
				return -1;
			}

			size_t i = wi->i + c->data.size() + 24;
			if (i < wi->i) {
				return -1;
			}

			wi->chunkCount = chunkCount;
			wi->chunkSize = chunkSize;
			wi->i = i;
		}

		// Init chunk header
		uint8_t header[24];
		byte::be::writeu64(header, c->id);
		byte::be::writeu64(header+8, c->data.size());
		// Subchunk len, filled prog

		// Write subchunks recursively
		for (uint32_t ic = 0; ic < c->children.size(); ++ic) {
			int r = writeChunk(&c->children[ic], wi);
			if (r != 0) {
				return r;
			}
		}

		byte::be::writeu64(header+16, wi->i - (previ + c->data.size() + 24));
		// ^ Note that this is the difference between the END of this
		// chunk (including data) and the END of the last chunk
		// (including data)
		fseek(wi->f, previ, SEEK_SET);
		fwrite((const void*)header, 1, 24, wi->f);

		// Write chunk data
		fseek(wi->f, previ+24, SEEK_SET);
		fwrite((const void*)c->data.data(), 1, c->data.size(), wi->f);
		return 0;
	}

	int writeFile(const char* filename, file* f) {
		FILE* fstd = fopen(filename, "wb");
		if (!fstd) {
			dbg::log("Write: .yak failed to open file \"" + std::string(filename) + "\"\n");
			return -1;
		}

		// '.yak' beginning stuff
		uint8_t yak[33];
		yak[4] = 1; // Version

		byte::be::writeu32(yak, 0x2E79616B); // '.yak'
		// Total chunk count, filled prog
		// Total chunk size, filled prog
		byte::be::writeu64(yak+17, f->claimer);
		byte::be::writeu64(yak+25, f->identif);

		// Write each chunk
		writeCi wi = {};
		wi.f = fstd;
		wi.i = 33;
		wi.chunkCount = 0;
		wi.chunkSize = 0;
		if (writeChunk(&f->c, &wi) != 0) {
			fclose(fstd);
			dbg::log("Write: .yak write chunk call failed\n");
			return -1;
		}

		// Finalise yak beginning stuff
		byte::be::writeu32(yak+5, wi.chunkCount);
		byte::be::writeu64(yak+9, wi.chunkSize);
		fseek(fstd, 0, SEEK_SET);
		fwrite((const void*)yak, 1, 33, fstd);
		fclose(fstd);
		return 0;
	}

	// Var names here aren't confusing at all
	chunk* findChunk(chunk* c, uint64_t id, uint32_t* ci) {
		uint32_t p;
		if (!ci) {
			p = 0;
			ci = &p;
		}

		for (uint32_t ic = *ci; ic < c->children.size(); ++ic) {
			if (c->children[ic].id == id) {
				*ci = ic + 1;
				return &c->children[ic];
			}
		}
		return 0;
	}
}