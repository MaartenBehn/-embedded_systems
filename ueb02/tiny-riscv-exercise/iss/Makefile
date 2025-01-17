all: isa

build/Makefile:
	mkdir -p build
	cd build && cmake ..

isa: build/Makefile
	make -C build

clean:
	rm -r build
