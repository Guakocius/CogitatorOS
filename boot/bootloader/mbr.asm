[bits 16]
[org 0x7C00] ; BIOS loads the boot sector into memory location 0x7c00

;
; FAT12 Header
;
jmp short start
nop

bdb_oem:                      db 'MSWIN4.1'         ; 8 bytes
bdb_bytes_per_sector:         dw 512
bdb_sectors_per_cluster:      db 1
bdb_reserved_sectors:         dw 1
bdb_fat_count:                db 2
bdb_dir_entries_count:        dw 0E0h
bdb_total_sectors:            dw 2880               ; 2880 * 512 = 1.44MB
bdb_media_descriptor_type:    db 0F0h               ; F0 = 3.5" floppy disk
bdb_sectors_per_fat:          dw 9                  ; 9 sectors/fat
bdb_sectors_per_track:        dw 18
bdb_heads:                    dw 2
bdb_hidden_sectors:           dd 0
bdb_large_sector_count:       dd 0

; extended boot record
ebr_drive_number:             db 0                  ; 0x00 = floppy, 0x80 = hdd
                              db 0                  ; reserved
ebr_signature:                db 29h
ebr_volume_id:                db 12h, 34h, 56h, 78h ; serial number
ebr_volume_label:             db 'COGITATOR OS'        ; 11 bytes, padded with spaces
ebr_system_id:                db 'FAT12   '         ; 8 bytes

;
; Code goes here
;

start:
    KERNEL_OFFSET equ 0x1000

    mov [BOOT_DRIVE], dl ; Save the boot drive number

        ; Setup stack
    mov bp, 0x9000
    mov sp, bp

;start:
;   jmp main

    mov ah, 0x0E
    mov al, 0x48 ; 'H'
    mov bh, 0x00
    int 0x10

    call load_kernel

    %include "./boot/bootloader/disk.asm"
    %include "./boot/bootloader/gdt.asm"
    %include "./boot/bootloader/32-bit-switch.asm"

    load_kernel:
        mov al, 0x57 ; 'W'
        int 0x10

        mov bx, KERNEL_OFFSET ; bx -> destination
        mov dh, 0x05 ; dh -> number of sectors to read
        mov dl, [BOOT_DRIVE] ; dl -> disk

        call disk_load

        ;call switch_to_32bit

[bits 32]
BEGIN_32_BIT:
    jmp KERNEL_OFFSET ; Call the kernel
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0 ; Pad the rest of the sector with zeros to make it 512 bytes
dw 0xAA55 ; Boot signature, magic number
