.PHONY: all bootloader libc drivers cpu kernel clean run

all: os.img

# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

bootloader:
	make -C bootloader	

libc:
	make -C libc

drivers: libc
	make -C drivers

cpu: libc
	make -C cpu

kernel: drivers cpu
	make -C kernel

# This is the actual disk image that the computer loads ,
# which is the combination of our compiled bootsector and kernel
os.img: bootloader kernel
	cat bootloader/bootloader.bin kernel/kernel.bin > os.img

run: os.img
	qemu-system-i386 -fda os.img

# -s  Shorthand for -gdb tcp::1234, i.e. open a gdbserver on TCP port 1234.
debug: os.img
	make debug -C kernel
	qemu-system-i386 -gdb tcp::1234 -fda os.img &
	gdb -ex "target remote localhost:1234" -ex "symbol-file ./kernel/kernel.elf"

clean:
	rm -f os.img
	make clean -C libc
	make clean -C drivers
	make clean -C cpu
	make clean -C kernel
	make clean -C bootloader