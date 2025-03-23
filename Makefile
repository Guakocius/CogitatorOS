CC = gcc
ASM = nasm
CFLAGS = -ffreestanding -fno-pic -mno-red-zone -I./boot/drivers/include -I./boot/bootloader/kernel/include
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

./bin/kernel.bin: ./boot/bootloader/kernel-entry.o ./boot/drivers/ports.o ./boot/drivers/display.o ./boot/bootloader/kernel/util.o ./boot/bootloader/kernel/kernel.o 
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

./boot/bootloader/kernel-entry.o: ./boot/bootloader/kernel-entry.asm
	$(ASM) $< -f elf -o $@

./boot/bootloader/kernel/kernel.o: ./boot/bootloader/kernel/kernel.c
	$(CC) -m32 -ffreestanding -c $< -o $@ $(CFLAGS)

./bin/mbr.bin: ./boot/bootloader/mbr.asm
	$(ASM) $< -f bin -o $@

./boot/drivers/display.o: ./boot/drivers/display.c
	$(CC) -m32 -ffreestanding -c $< -o $@ $(CFLAGS)

./boot/drivers/ports.o: ./boot/drivers/ports.c
	$(CC) -m32 -ffreestanding -c $< -o $@ $(CFLAGS)

./boot/bootloader/kernel/util.o: ./boot/bootloader/kernel/util.c
	$(CC) -m32 -ffreestanding -c $< -o $@ $(CFLAGS)

./bin/CogitatorOS.bin: ./bin/mbr.bin ./bin/kernel.bin
	cat $^ > $@

./boot/img/CogitatorOS.img: ./bin/CogitatorOS.bin
	mkdir -p ./boot/img
	cp $< $@

run: ./boot/img/CogitatorOS.img
	qemu-system-i386 -drive format=raw,file=$<

%.o: %.c
	$(CC) -fPIE -c -o $@ $< $(CFLAGS)

clean:
	rm -f ./bin/*.bin ./boot/bootloader/*.o ./boot/bootloader/kernel/*.o ./boot/drivers/*.o $(IMG)
