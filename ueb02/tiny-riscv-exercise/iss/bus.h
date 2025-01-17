#pragma once
#include <inttypes.h>
#include <list>

typedef uint32_t Address;

class MemoryMappedDevice {
public:
	virtual ~MemoryMappedDevice(){};
	virtual uint32_t load_data(const Address addr) = 0;
	virtual void store_data(const Address addr, const uint32_t value) = 0;
};

struct Bus {
	struct Mapping {
		Address from;
		Address to;
		MemoryMappedDevice *dev;
	};

	std::list<Mapping> map;
	Mapping findMapping(const Address addr);

    /*  interface to the ISS */

    int32_t load_word(const Address addr);
    void store_word(const Address addr, const uint32_t value);
};

