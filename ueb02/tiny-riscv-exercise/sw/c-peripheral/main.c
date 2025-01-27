#include <inttypes.h>

enum Syscalls {
    printInt = 1,		// Prints a0 as integer
	printChar = 2,		// Prints a0 as ASCII char
    printString = 3,	// Prints a null-terminated string from a0
    SYS_exit = 93
};

struct PrinterPeripheral {
	volatile uint32_t selector;
	volatile uint32_t value;
};
struct PrinterPeripheral* const printer = (struct PrinterPeripheral*) 0x900000;

int main() {
    register int num asm ("a7");
	register int param1 asm ("a0");
	register int ret asm ("a0");

    printer->selector = 0;

    num = printString;
    param1 = "Random Numbers: ";
    asm volatile
    (
    "ecall"
    : "=r" (ret)
    : "r" (num), "r" (param1)
    );
    for (int i = 0; i < 128; i++) {
        num = printInt;
        param1 = printer->value;
        asm volatile
        (
        "ecall"
        : "=r" (ret)
        : "r" (num), "r" (param1)
        );

        num = printString;
        param1 = " ";
        asm volatile
        (
        "ecall"
        : "=r" (ret)
        : "r" (num), "r" (param1)
        );
    }
    num = printString;
	param1 = "\n";
	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);



    printer->selector = 1;

    num = printString;
    param1 = "Random Chars: ";
    asm volatile
    (
    "ecall"
    : "=r" (ret)
    : "r" (num), "r" (param1)
    );
    for (int i = 0; i < 128; i++) {
        num = printChar;
        param1 = printer->value;
        asm volatile
        (
        "ecall"
        : "=r" (ret)
        : "r" (num), "r" (param1)
        );

        num = printString;
        param1 = " ";
        asm volatile
        (
        "ecall"
        : "=r" (ret)
        : "r" (num), "r" (param1)
        );
    }
    num = printString;
	param1 = "\n";
	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);




    printer->selector = 2;

    num = printString;
    param1 = "Song: ";
    asm volatile
    (
    "ecall"
    : "=r" (ret)
    : "r" (num), "r" (param1)
    );
    for (int i = 0; i < 128; i++) {
        num = printChar;
        param1 = printer->value;
        asm volatile
        (
        "ecall"
        : "=r" (ret)
        : "r" (num), "r" (param1)
        );
    }
    num = printString;
	param1 = "\n";
	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);

    return 0;
}

