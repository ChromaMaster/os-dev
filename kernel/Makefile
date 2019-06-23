.PHONY: all

GCC=gcc
GCC_FLAGS=-ffreestanding -m32 -fno-pie	

C_SOURCES = $(wildcard *.c ../drivers/*.c ../lib/*.c)
HEADERS = $(wildcard *.h ../drivers/*.h ../lib/*.h)

# Convert the *. c filenames to *. o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

# all: kernel.dump kernel.bin kernel.dis

$(info "C_SOURCES: ${C_SOURCES}")
$(info "HEADERS: ${HEADERS}")
$(info "OBJ: ${OBJ}")

all: kernel.bin
debug: kernel.dump kernel.dis

# Build our object file .
%.o: %.c ${HEADERS}
	${GCC} ${GCC_FLAGS} -c $< -o $@

# Build our kernel entry object file .
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.dump: kernel.o
	objdump -m i386 -d $< > $@

# This builds the binary of our kernel from two object files :
# - the kernel_entry , which jumps to main() in our kernel
# - the compiled C kernel
kernel.bin: kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary	

kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@

clean:
	rm -f *.o kernel.dump kernel.bin kernel.dis
