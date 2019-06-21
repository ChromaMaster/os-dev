.PHONY: bootloader kernel os_image

all: bootloader kernel os.img

bootloader:
	make -C bootloader	

kernel:
	make -C kernel

os.img: bootloader kernel
	cat bootloader/bootloader.bin kernel/kernel.bin > os.img

run: os_image
	qemu-system-i386 os.img

clean:
	rm os.img
	make clean -C kernel
	make clean -C bootloader