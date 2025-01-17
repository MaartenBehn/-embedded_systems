#include <inttypes.h>

struct PrinterPeripheral {
	volatile uint32_t selector;
	volatile uint32_t value;
};
struct PrinterPeripheral* const printer = (struct PrinterPeripheral*) 0x900000;

int main() {
    // TODO
    return 0;
}
