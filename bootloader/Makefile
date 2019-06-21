.PHONY: all

all: bootloader.bin

bootloader.bin:
	nasm -f bin bootloader.asm -o bootloader.bin

clean:
	rm bootloader.bin