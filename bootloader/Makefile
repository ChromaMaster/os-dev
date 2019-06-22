.PHONY: all

all: bootloader.bin

# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

# Assemble the boot sector to raw machine code
bootloader.bin: bootloader.asm
	nasm -f bin $^ -o $@

clean:
	rm -f bootloader.bin