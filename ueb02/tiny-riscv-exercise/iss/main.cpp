#include <cstdlib>

#include "iss.h"
#include "elf_loader.h"
#include "bus.h"
#include "memory.hpp"
#include "peripheral.hpp"

static constexpr size_t MEM_SIZE = 1024*1024*8;  // 8 MB ram

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "ERROR: input program expected" << std::endl;
        return -1;
    }

    ISS sim;
    Memory mem(MEM_SIZE);
    CharacterPrinter printer;
    Bus bus;
    ELFLoader loader(argv[1]);

    // connecting all memory mapped devices
    bus.map.emplace_front(Bus::Mapping{.from = 0x0, .to = MEM_SIZE, .dev = &mem});
    // TODO: Task 5

    // The following line is only valid if memory starts at 0x0!
    loader.load_executable_image(mem.misaligned_mem, mem.size_bytes);

    sim.init(&bus, loader.get_entrypoint(), MEM_SIZE-sizeof(uint64_t));

    sim.run();
    sim.show();

	return 0;
}
