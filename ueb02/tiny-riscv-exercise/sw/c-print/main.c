#include <inttypes.h>

enum Syscalls {
    printInt = 1,		// Prints a0 as integer
	printChar = 2,		// Prints a0 as ASCII char
    printString = 3,	// Prints a null-terminated string from a0
    SYS_exit = 93
};

int32_t syscall(const uint32_t syscall, const uint32_t par1) {
    register int num asm ("a7") = syscall;
	register int param1 asm ("a0") = par1;
	register int ret asm ("a0");
	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);
	return 0;
}

int x = 5;
int y;

int main() {
	int a = 6;
	int b = 7;
	a = a + b + x + y;
	syscall(printInt, 42);
	syscall(printChar, 'a'); // a
	
	syscall(printString, "a + b + x + y = ");
	syscall(printInt, a);
	syscall(printString, "\n");
	return a;
}


