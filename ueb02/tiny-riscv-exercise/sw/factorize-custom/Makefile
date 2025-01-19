CC=riscv32-none-elf

all : factor.o
	$(CC)-ld factor.o -o main

factor.o : factor.S
	$(CC)-as factor.S -o factor.o -march=rv32im -mabi=ilp32

dump-elf: all
	$(CC)-readelf -a main

dump-code: all
	$(CC)-objdump -D main

sim: all
	../../iss/build/riscv-tiny-isa main

clean:
	rm -f main *.o
