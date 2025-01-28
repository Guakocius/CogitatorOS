CC = gcc
ASM = nasm
CFLAGS = -lncurses -I./kernel/include
#LDFLAGS = -lncurses
SOURCES = $(wildcard ./src/*.c)
ASM_SOURCES = $(wildcard ./boot/bios/*.asm ./boot/bootloader/*.asm)
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
#	$(CC) -o $(EXEC) $(SOURCES) $(CFLAGS)
#	$(CC) $(OBJECTS) -o $(EXEC) $(LDFLAGS)
#	$(ASM) -f bin -o ./bin/bios.bin $(ASM_SOURCES)
	$(CC) -o $(EXEC) $(OBJECTS) $(CFLAGS)
#	$(ASM) -f bin -o ./bin/bios.bin $(ASM_SOURCES)

$(IMG):
	@echo "Creating image..."
	@dd if=/dev/zero of=$(IMG) bs=512 count=2880
	@dd if=./bin/boot.bin of=$(IMG) bs=512 count=1 conv=notrunc
	@dd if=./bin/bios.bin of=$(IMG) bs=512 seek=1 conv=notrunc
	@dd if=./bin/graphics.bin of=$(IMG) bs=512 seek=2 conv=notrunc
	@dd if=./bin/CogitatorOS of=$(IMG) bs=512 seek=3 conv=notrunc

boot.bin: ./boot/bootloader/boot.asm
	$(ASM) -f bin -o ./bin/boot.bin ./boot/bootloader/boot.asm

bios.bin: ./boot/bios/bios.asm
	$(ASM) -f bin -o ./bin/bios.bin ./boot/bios/bios.asm

graphics.bin: ./boot/bios/graphics.asm
	$(ASM) -f bin -o ./bin/graphics.bin ./boot/bios/graphics.asm

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f ./bin/boot.bin ./bin/bios.bin ./bin/graphics.bin $(OBJECTS)
