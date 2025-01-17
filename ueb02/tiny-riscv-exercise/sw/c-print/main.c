#include <inttypes.h>

enum Syscalls {
    printInt = 1,		// Prints a0 as integer
	printChar = 2,		// Prints a0 as ASCII char
    printString = 3,	// Prints a null-terminated string from a0
    SYS_exit = 93
};

int32_t syscall(const uint32_t syscall, const uint32_t par1) {
    // TODO
    return 0;
}

int x = 5;
int y;

int main() {
	int a = 6;
	int b = 7;
	a = a + b + x + y;
	syscall(printString, "a + b + x + y = ");
	syscall(printInt, a);
	syscall(printString, "\n");
	return a;
}
