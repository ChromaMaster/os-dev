.PHONY: all

# GCC=gcc
GCC=/usr/local/cross/bin/i686-elf-gcc

# -ffreestanding: Assert that compilation targets a freestanding environment.
# A freestanding environment is one in which the standard library may not exist
# -m32 stack alignment
# -fno-pie: That flag is telling gcc not to make a position independent 
# executable (PIE). PIE is a security feature where the kernel loads the binary 
# and dependencies into a random location of virtual memory each time it's run.
# -g: Produce debugging information in the operating system's native format 
# (stabs, COFF, XCOFF, or DWARF).
GCC_FLAGS=-ffreestanding -m32 -g

C_SOURCES = $(wildcard *.c ../drivers/*.c ../libc/*.c ../cpu/*.c)
HEADERS = $(wildcard *.h ../drivers/*.h ../libc/*.h ../cpu/*.h)

# Convert the *. c filenames to *. o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o ../cpu/interrupt.o}

# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

# all: kernel.dump kernel.bin kernel.dis

$(info "C_SOURCES: ${C_SOURCES}")
$(info "HEADERS: ${HEADERS}")
$(info "OBJ: ${OBJ}")

all: kernel.bin

debug: kernel.dump kernel.dis kernel.elf

# Build our object file .
%.o: %.c ${HEADERS}
	${GCC} ${GCC_FLAGS} -c $< -o $@

# Build our kernel entry object file .
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.dump: kernel.o
	objdump -m i386 -d $< > $@

# Just for debugging
kernel.elf: kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ 

# This builds the binary of our kernel from two object files :
# - the kernel_entry , which jumps to main() in our kernel
# - the compiled C kernel
kernel.bin: kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary	

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

clean:
	rm -f *.o kernel.dump kernel.bin kernel.dis
