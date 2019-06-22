.PHONY: all bootloader kernel os_image clean run

all: bootloader kernel os.img

# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

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