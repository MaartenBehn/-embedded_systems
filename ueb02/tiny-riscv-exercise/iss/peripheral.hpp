/*
 * peripheral.hpp
 *
 *  Created on: Oct 27, 2022
 *      Author: pp
 */

#pragma once

#include "bus.h"

struct CharacterPrinter : public MemoryMappedDevice {
    // TODO: Task 5

	uint32_t load_data(const Address addr) override;

	void store_data(const Address addr, const uint32_t value) override;
};
