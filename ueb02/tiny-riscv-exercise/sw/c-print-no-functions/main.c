#include <inttypes.h>

enum Syscalls {
    printInt = 1,		// Prints a0 as integer
	printChar = 2,		// Prints a0 as ASCII char
    printString = 3,	// Prints a null-terminated string from a0
    SYS_exit = 93
};

int x = 5;
int y;

int main() {
	int a = 6;
	int b = 7;
	a = a + b + x + y;

	// syscall(printString, "a + b + x + y = ");
	register int num asm ("a7") = printString;
	register int param1 asm ("a0") = "a + b + x + y = ";
	register int ret asm ("a0");

	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);

	// syscall(printInt, a);
	num = printInt;
	param1 = a;
	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);

	// syscall(printString, "\n");
	num = printString;
	param1 = "\n";

	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);

	return a;
}


