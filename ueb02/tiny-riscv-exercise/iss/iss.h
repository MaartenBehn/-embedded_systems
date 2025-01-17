#pragma once

#include <stdint.h>

#include "bus.h"
#include "register.hpp"

struct ISS {
    enum Syscalls {
        printInt = 1,		// Prints a0 as integer
		printChar = 2,		// Prints a0 as ASCII char
        printString = 3,	// Prints a null-terminated string from a0
        SYS_exit = 93
    };


    Bus *bus = nullptr;
    RegFile regs;
    long unsigned number_of_steps_executed = 0;
    uint32_t pc;
    uint32_t last_pc;
    bool shall_exit = false;

    void run_step();

    void init(Bus *bus, Address entrypoint, Address stackpointer);

    void run();

    void show();
};
