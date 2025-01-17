/*
 * memory.hpp
 *
 *  Created on: Oct 27, 2022
 *      Author: pp
 */

#pragma once

#include "bus.h"
#include <inttypes.h>
#include <string>

struct Memory : public MemoryMappedDevice
{
	typedef uint32_t Datatype;
	Datatype* mem;
	uint8_t* misaligned_mem;	// pointer of different width to mem
	Address size_bytes;
	Memory(Address size_bytes) : size_bytes(size_bytes), mem(nullptr), misaligned_mem(nullptr){
		mem = new Datatype[size_bytes/sizeof(Datatype)];
		misaligned_mem = reinterpret_cast<uint8_t*>(mem);
	}

	~Memory() {
		delete[] mem;
	}

	uint32_t load_data(const Address addr) override {
		assert (addr < size_bytes && "Read access of memory outside size!");

		const Address aligned_addr = addr/sizeof(Datatype);
		if(addr % sizeof(Datatype) == 0)
			return mem[aligned_addr];

		// misaligned access
		uint32_t ret;
		memcpy(&ret, &misaligned_mem[addr], sizeof(Datatype));
		return ret;
	}

	void store_data(const Address addr, const uint32_t value) override {
		assert (addr < size_bytes && "Write access of memory outside size!");
		const Address aligned_addr = addr/sizeof(Datatype);
		if(addr % sizeof(Datatype) == 0) {
			mem[aligned_addr] = value;
			return;
		}

		// misaligned access
		memcpy(&misaligned_mem[addr], &value, sizeof(Datatype));
	}
};
