#include <inttypes.h>

enum Syscalls {
	printInt = 1,		// Prints a0 as integer
	printString = 2,	// Prints a null-terminated string from a0
	SYS_exit = 93
};

inline int32_t syscall(const uint32_t syscall, uint32_t par1){
	register int num asm ("a7") = syscall;
	register int param1 asm ("a0") = par1;
	register int ret asm ("a0");
	asm volatile
	(
	"ecall"
	: "=r" (ret)
	: "r" (num), "r" (param1)
	);
	return ret;
}

