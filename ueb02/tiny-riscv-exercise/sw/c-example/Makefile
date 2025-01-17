CC=riscv32-none-elf

all : main.c sum.c bootstrap.S
	$(CC)-gcc main.c sum.c bootstrap.S -o main -march=rv32i -mabi=ilp32 -nostartfiles -Wl,-no-relax

dump-elf: all
	$(CC)-readelf -a main

dump-code: all
	$(CC)-objdump -D main

dump-asm: all
	$(CC)-objdump -S main

sim: all
	../../iss/build/riscv-tiny-isa main

clean:
	rm -f main
