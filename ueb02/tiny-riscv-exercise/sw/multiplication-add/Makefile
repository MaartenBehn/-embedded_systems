all : mul.o
	riscv32-none-elf-ld mul.o -o main

mul.o : mul.S
	riscv32-none-elf-as mul.S -o mul.o -march=rv32i -mabi=ilp32

dump-elf: all
	riscv32-none-elf-readelf -a main

dump-code: all
	riscv32-none-elf-objdump -D main

sim: all
	../../iss/build/riscv-tiny-isa main

clean:
	rm -f main mul.o
