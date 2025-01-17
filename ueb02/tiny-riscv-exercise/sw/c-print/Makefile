all : main.c bootstrap.S
	riscv32-none-elf-gcc main.c bootstrap.S -o main -march=rv32i -mabi=ilp32 -nostartfiles -Wl,-no-relax

dump-elf: all
	riscv32-none-elf-readelf -a main

dump-code: all
	riscv32-none-elf-objdump -D main

dump-asm: all
	riscv32-none-elf-objdump -S main

sim: all
	../../iss/build/riscv-tiny-isa main

dump-comment: all
	objdump -s --section .comment main

clean:
	rm -f main
