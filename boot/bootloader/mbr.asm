[bits 16]
[org 0x7C00] ; BIOS loads the boot sector into memory location 0x7c00

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl ; Save the boot drive number

; Setup stack
mov bp, 0x9000
mov sp, bp

call load_kernel
call switch_to_32bit

jmp $ ; Infinite loop

%include "./boot/bootloader/disk.asm"
%include "./boot/bootloader/gdt.asm"
%include "./boot/bootloader/32-bit-switch.asm"

[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; bx -> destination
    mov dh, 2 ; dh -> number of sectors to read
    mov dl, [BOOT_DRIVE] ; dl -> disk
    call disk_load
    ret

[bits 32]
BEGIN_32_BIT:
    call KERNEL_OFFSET ; Call the kernel
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0 ; Pad the rest of the sector with zeros to make it 512 bytes
dw 0xAA55 ; Boot signature, magic number
