git clone https://github.com/cirromulus/riscv-gnu-toolchain
cd riscv-gnu-toolchain

#fix binutils
rm -r riscv-binutils
git submodule add --force https://github.com/Cirromulus/riscv-binutils-gdb.git riscv-binutils
#fix opcodes
rm -r riscv-opcodes
git submodule add --force https://github.com/Cirromulus/riscv-opcodes.git riscv-opcodes

#cloning quemu seems to be very slow using cli sometimes
# try this if cloning qemu fails
curl -L https://github.com/riscvarchive/riscv-qemu/archive/ff36f2f77ec3e6a6211c63bfe1707ec057b12f7d.zip -o qemu.zip
git rm riscv-qemu
mkdir riscv-qemu
bsdtar xvf qemu.zip --strip-components=1 -C ./riscv-qemu/

git submodule update --init --recursive

./configure --prefix=$(pwd)/install --with-arch=rv32ima --with-abi=ilp32
make all build-newlib

#export PATH=/path/to/the/toolchain/riscv-gnu-toolchain/install/bin/:$PATH

