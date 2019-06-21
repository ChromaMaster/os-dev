.PHONY: all

GCC=gcc
GCC_FLAGS=-ffreestanding -m32 -fno-pie
all: kernel.o kernel.dump kernel.bin kernel.dis
	
kernel.o:
	${GCC} ${GCC_FLAGS} -c kernel.c -o kernel.o

kernel.dump: kernel.o
	objdump -m i386 -d kernel.o > kernel.dump

kernel.bin: kernel.o
	ld -m elf_i386 -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary

kernel.dis: kernel.bin
	ndisasm -b 32 kernel.bin > kernel.dis

clean:
	rm kernel.o kernel.dump kernel.bin kernel.dis
