# Makefile for OS

# constants
OBJS=boot.asm print_string_pm.asm gdt.asm \
	switch_to_pm.asm print_string.asm disk_load.asm
VPATH=boot boot/print boot/gdt boot/disk boot/utils kernel

# build
build: boot.bin kernel.bin
	cat boot.bin kernel.bin > os-image
	qemu-system-i386 -drive format=raw,file=os-image

boot.bin: $(OBJS)
	nasm boot/boot.asm -f bin -o boot.bin

kernel.bin: kernel.o
	ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary

kernel.o: kernel.c
	gcc -ffreestanding -c kernel/kernel.c -o kernel.o

clean:
	rm -rf *.bin
	rm -rf kernel.o
	rm -rf os-image
