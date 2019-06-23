.PHONY: all

GCC=gcc
GCC_FLAGS=-ffreestanding -m32 -fno-pie	

C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

# Convert the *. c filenames to *. o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

# $< is the first dependancy
# $^ is substituted with all of the target’s dependancy files
# $@ is the target file

all: ${OBJ}

# Build our object file .
%.o: %.c %.h
	${GCC} ${GCC_FLAGS} -c $< -o $@

clean:
	rm -f *.o
