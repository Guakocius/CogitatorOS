CC = gcc
ASM = nasm
CFLAGS = -ffreestanding -fno-pic -mno-red-zone
LDFLAGS = -pie
SOURCES = $(wildcard ./src/*.c)
ASM_SOURCES = $(wildcard ./boot/bios/*.asm ./boot/bootloader/*.asm)
OBJECTS = $(SOURCES:.c=.o)
IMG = ./boot/img/CogitatorOS.img

all: install_deps run

install_deps:
	@echo "Installing dependencies..."

	@if [ -f /etc/arch-release ]; then \
		if ! pacman -Qi ncurses >/dev/null 2>&1; then \
			sudo pacman -Sy --noconfirm ncurses; \
		fi; \
		if ! pacman -Qi gcc-multilib >/dev/null 2>&1; then \
			sudo pacman -Sy --noconfirm gcc-multilib; \
		fi; \
		if ! pacman -Qi glibc >/dev/null 2>&1; then \
			sudo pacman -Sy --noconfirm glibc; \
		fi; \
	else \
		if ! dpkg -s libncurses5-dev >/dev/null 2>&1; then \
			sudo apt update && sudo apt upgrade -y libncurses5-dev; \
		fi; \
		if ! dpkg -s gcc-multilib >/dev/null 2>&1; then \
			sudo apt update && sudo apt upgrade -y gcc-multilib; \
		fi; \
		if ! dpkg -s libc6-dev-i386 >/dev/null 2>&1; then \
			sudo apt update && sudo apt upgrade -y libc6-dev-i386; \
		fi; \
	fi

./bin/kernel.bin: ./boot/bootloader/kernel-entry.o ./boot/bootloader/kernel.o
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

./boot/bootloader/kernel-entry.o: ./boot/bootloader/kernel-entry.asm
	$(ASM) $< -f elf -o $@

./boot/bootloader/kernel.o: ./boot/bootloader/kernel.c
	$(CC) -m32 -ffreestanding -c $< -o $@ $(CFLAGS)

./bin/mbr.bin: ./boot/bootloader/mbr.asm
	$(ASM) $< -f bin -o $@

./bin/CogitatorOS.bin: ./bin/mbr.bin ./bin/kernel.bin
	cat $^ > $@

run: ./bin/CogitatorOS.bin
	qemu-system-i386 -fda $<

#$(IMG): ./bin/mbr ./bin/bios ./bin/graphics
#	@echo "Creating image..."
#	@dd if=/dev/zero of=$(IMG) bs=512 count=2880
#	@dd if=./bin/mbr of=$(IMG) bs=512 count=1 conv=notrunc
#	@dd if=./bin/bios of=$(IMG) bs=512 seek=1 conv=notrunc
#	@dd if=./bin/graphics of=$(IMG) bs=512 seek=2 conv=notrunc
#	@echo "Image created"

%.o: %.c
	$(CC) -fPIE -c -o $@ $< $(CFLAGS)

clean:
	rm -f ./bin/*.bin ./boot/bootloader/*.o
