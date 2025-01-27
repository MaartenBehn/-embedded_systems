CC=riscv32-none-elf

OBJ := print.o

all : $(OBJ)
	$(CC)-ld $(wildcard *.o) -o print

%.o : %.S
	$(CC)-as $^ -o $@ -march=rv32im -mabi=ilp32

dump-elf: all
	$(CC)-readelf -a print

dump-code: all
	$(CC)-objdump -D print

sim: all
	../../iss/build/riscv-tiny-isa print

clean:
	rm -f print *.o
