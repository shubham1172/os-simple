# Makefile for OS
# Note: $^ = all dependencies, $< = first dependency, $@ = target


# Generate list of sources using wildcards
C_SOURCES= $(wildcard kernel/*.c drivers/*/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*/*.h)

# List of objects to build
OBJ = ${C_SOURCES:.c=.o}

all: os-image

# run
run: all
	qemu-system-i386 -drive format=raw,file=os-image

# build
os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image


kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -melf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity, the C files depend on all header files
%.o : %.c ${HEADERS}
	gcc -m32 -fno-PIC -ffreestanding -c $< -o $@

# Assemble the kernel_entry
%.o : %.asm
	nasm $< -f elf32 -o $@

%.bin : %.asm
	nasm $< -f bin -o $@

clean :
	rm -rf *.bin *.dis *.o os-image
	rm -rf kernel/*.o boot/*.bin drivers/*/*.o
