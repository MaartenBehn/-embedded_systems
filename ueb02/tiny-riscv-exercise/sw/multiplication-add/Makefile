all : mul.o
	riscv32-unknown-elf-ld mul.o -o main

mul.o : mul.S
	riscv32-unknown-elf-as mul.S -o mul.o -march=rv32i -mabi=ilp32

dump-elf: all
	riscv32-unknown-elf-readelf -a main

dump-code: all
	riscv32-unknown-elf-objdump -D main

sim: all
	../../isa/build/lib/riscv-tiny-isa main

clean:
	rm -f main mul.o
