[bits 16]
[org 0x7C00] ; BIOS loads the boot sector into memory location 0x7c00

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl ; Save the boot drive number

; Setup stack
mov bp, 0x9000
mov sp, bp

mov ah, 0x0E
mov al, 'H'
int 0x10
call load_kernel

%include "./boot/bootloader/disk.asm"
%include "./boot/bootloader/gdt.asm"
%include "./boot/bootloader/32-bit-switch.asm"

load_kernel:
    mov ah, 0x0E
    mov al, 'W'
    int 0x10
    mov bx, KERNEL_OFFSET ; bx -> destination
    mov dh, 2 ; dh -> number of sectors to read
    mov dl, [BOOT_DRIVE] ; dl -> disk
    call clear_screen
    call disk_load
    call switch_to_32bit

    jmp $

clear_screen:
    pusha
    
    mov ah, 0x07
    mov bh, 0x0F
    mov cx, 0x00
    mov dx, 0x184F
    int 0x10

    mov ah, 0x02
    mov dh, 0x00
    mov dl, 0x00
    mov bh, 0x00
    int 0x10

    popa
    ret

[bits 32]
BEGIN_32_BIT:
    jmp KERNEL_OFFSET ; Call the kernel
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0 ; Pad the rest of the sector with zeros to make it 512 bytes
dw 0xAA55 ; Boot signature, magic number
