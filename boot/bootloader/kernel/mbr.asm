[bits 16]
[org 0x7C00] ; BIOS loads the boot sector into memory location 0x7C00

KERNEL_OFFSET equ 0x1000 ; Physical load address of the 32-bit kernel

mov [BOOT_DRIVE], dl ; Save the boot drive number from BIOS

; Setup a small real-mode stack
mov bp, 0x9000
mov sp, bp

; Print 'H'
mov ah, 0x0E
mov al, 0x48 ; 'H'
mov bh, 0x00
int 0x10

call load_kernel
; Should never return here, but halt just in case
jmp $

%include "./boot/bootloader/disk.asm"
%include "./boot/bootloader/gdt.asm"
%include "./boot/bootloader/32-bit-switch.asm"

[bits 16]  ; Ensure we're back in 16-bit mode for load_kernel
; Load the kernel from disk into memory and enter protected mode
load_kernel:
    ; Print 'W'
    mov ah, 0x0E
    mov al, 0x57 ; 'W'
    int 0x10

    ; ES:BX points to destination buffer for int 13h reads
    xor ax, ax
    mov es, ax
    mov bx, KERNEL_OFFSET ; bx -> destination

    ; Read enough sectors to load the kernel (kernel.bin is ~2.6KB = 6 sectors)
    ; Round up and add extra for safety
    mov dh, 0x08 ; dh -> number of sectors to read (8 sectors = 4 KiB, plenty of room)
    mov dl, [BOOT_DRIVE] ; dl -> disk

    call disk_load

    ; Print 'P' to show we're about to enter protected mode
    mov ah, 0x0E
    mov al, 'P'
    int 0x10

    ; Switch to 32-bit protected mode and continue there
    call switch_to_32bit

; After switch_to_32bit, control jumps to init_32_bit and then here
[bits 32]
BEGIN_32_BIT:
    ; Print '3' to VGA to show we entered 32-bit mode
    mov byte [0xB8000], '3'
    mov byte [0xB8001], 0x0F

    jmp KERNEL_OFFSET ; Jump to the 32-bit kernel entry at 0x1000
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0 ; Pad the rest of the sector with zeros to make it 512 bytes
dw 0xAA55 ; Boot signature, magic number
