CC = gcc
ASM = nasm
CFLAGS = -lncurses -I./kernel/include
SOURCES = $(wildcard ./src/*.c)
ASM_SOURCES = $(wildcard ./boot/bios/*.asm ./boot/bootloader/*.asm)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)
OBJECTS = $(SOURCES:.c=.o)
EXEC = ./bin/CogitatorOS
IMG = ./boot/img/CogitatorOS.img

all: install_deps $(EXEC) $(IMG) clean

install_deps:
	@echo "Installing dependencies..."
	@if ! dpkg -s libncurses5 >/dev/null 2>&1; then \
		sudo apt update && sudo apt upgrade -y libncurses5-dev; \
	fi

	@if ! dpkg -s gcc-multilib >/dev/null 2>&1; then \
		sudo apt update && sudo apt upgrade -y gcc-multilib; \
	fi

	@if ! dpkg -s libc6-dev-i386 >/dev/null 2>&1; then \
		sudo apt update && sudo apt upgrade -y libc6-dev-i386; \
	fi


$(EXEC): $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(CFLAGS)

$(IMG): boot.bin bios.bin graphics.bin
	@echo "Creating image..."
	@dd if=/dev/zero of=$(IMG) bs=512 count=2880
	@dd if=./bin/boot.bin of=$(IMG) bs=512 count=1 conv=notrunc
	@dd if=./bin/bios.bin of=$(IMG) bs=512 seek=1 conv=notrunc
	@dd if=./bin/graphics.bin of=$(IMG) bs=512 seek=2 conv=notrunc

boot.bin: ./boot/bootloader/boot.asm
	$(ASM) -f bin -o ./bin/boot.bin ./boot/bootloader/boot.asm

bios.bin: ./boot/bios/bios.o
	ld -m elf_i386 -Ttext 0x8000 --oformat binary -o ./bin/bios.bin ./boot/bios/bios.o

graphics.bin: ./boot/bios/graphics.o
	ld -m elf_i386 -Ttext 0x9000 --oformat binary -o ./bin/graphics.bin ./boot/bios/graphics.o

./boot/bios/%.o: ./boot/bios/%.asm
	$(ASM) -f elf -o $@ $<

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f ./bin/boot.bin ./bin/bios.bin ./bin/graphics.bin $(OBJECTS)
