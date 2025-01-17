
#include "bus.h"
#include <exception>
#include <iomanip>

Bus::Mapping Bus::findMapping(const Address addr) {
	for (const auto& mapping : map) {
		if (addr >= mapping.from && addr < mapping.to) {
			return mapping;
		}
	}
	std::stringstream stream;
	stream << "Access at addr 0x"  << std::hex << addr << " not mapped";
	throw std::runtime_error(stream.str());
}

int32_t Bus::load_word(const uint32_t addr) {
	const auto mapping = findMapping(addr);
	return mapping.dev->load_data(addr - mapping.from);
}

void Bus::store_word(const uint32_t addr, const uint32_t value) {
	const auto mapping = findMapping(addr);
	mapping.dev->store_data(addr - mapping.from, value);
}


