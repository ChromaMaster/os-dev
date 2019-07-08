.PHONY: all bootloader libc drivers kernel clean run

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

kernel: drivers
	make -C kernel

# This is the actual disk image that the computer loads ,
# which is the combination of our compiled bootsector and kernel
os.img: bootloader kernel
	cat bootloader/bootloader.bin kernel/kernel.bin > os.img

run: os.img
	qemu-system-i386 -fda os.img

clean:
	rm -f os.img
	make clean -C libc
	make clean -C drivers
	make clean -C kernel
	make clean -C bootloader