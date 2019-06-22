.PHONY: all

GCC=gcc
GCC_FLAGS=-ffreestanding -m32 -fno-pie
all: kernel.o kernel.dump kernel.bin kernel.dis
	
# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

kernel.o: kernel.c
	${GCC} ${GCC_FLAGS} -c $< -o $@

kernel.dump: kernel.o
	objdump -m i386 -d $< > $@

kernel.bin: kernel.o kernel_entry.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary	

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

clean:
	rm kernel_entry.o kernel.o kernel.dump kernel.bin kernel.dis
