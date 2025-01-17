CC=riscv32-none-elf

OBJ := sum.o

all : $(OBJ)
	$(CC)-ld $(wildcard *.o) -o main

%.o : %.S
	$(CC)-as $^ -o $@ -march=rv32im -mabi=ilp32

dump-elf: all
	$(CC)-readelf -a main

dump-code: all
	$(CC)-objdump -D main

sim: all
	../../iss/build/riscv-tiny-isa main

clean:
	rm -f main *.o
