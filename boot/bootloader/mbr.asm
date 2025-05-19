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
ebr_volume_label:             db 'COGITATOR OS'     ; 11 bytes, padded with spaces
ebr_system_id:                db 'FAT12   '         ; 8 bytes

;
; Code goes here
;

start:

    mov ah, 0x0E
    mov al, 'B'
    int 0x10
    xor ax, ax

    ; Set up data segments
    mov ax, 0
    mov ds, ax
    mov es, ax

    ; Setup stack
    mov ss, ax
    mov sp, 0x7C00


    ; read something from floppy disk
    ; BIOS should set DL to drive number
    mov [ebr_drive_number], dl

    mov ax, 1                                           ; LBA=1, second sector from disk
    mov cl, 1                                           ; 1 sector to read
    mov bx, 0x7E00                                      ; data should be after the bootloader
    call disk_read

    ;jmp KERNEL_OFFSET
    ;call BEGIN_32_BIT

    mov ah, 0x0E
    mov al, 0x48 ; 'H'
    mov bh, 0x00
    int 0x10

;    %include "./boot/bootloader/disk.asm"
    %include "./boot/bootloader/gdt.asm"
    %include "./boot/bootloader/32-bit-switch.asm"

    puts:
        push si
        push ax
        push bx

    ;
    ; Error handlers
    ;
    floppy_error:
        mov ah, 0x0E
        mov al, 'T'
        int 0x10
        mov si, MSG_READ_FAILED
        call puts
        jmp wait_key_and_reboot

    wait_key_and_reboot:
        mov ah, 0
        int 0x16                                    ; wait for keypress
        jmp 0x0FFFF:0                               ; jump to beginning of BIOS, should reboot


    .halt:
        cli                                         ; Disable interrupts, CPU can't get out of the HALT state
        hlt


    load_kernel:

        mov bx, 0x7E00 ; bx -> destination
        mov dh, 0x05 ; dh -> number of sectors to read
        mov dl, [ebr_drive_number] ; dl -> disk

        ;
        ; Disk routines
        ;

        ;
        ; Converts an LBA address to a CHS address
        ; Parameters:
        ;   - ax: LBA address
        ; Returns:
        ;   - cx [bits 0-5]: sector number
        ;   - cx [bits 6-15]: cylinder
        ;   - dh: head
        lba_to_chs:

            push ax
            push dx
            mov ah, 0x0E
            mov al, 'C'
            int 0x10

            xor dx, dx                          ; dx = 0
            div word [bdb_sectors_per_track]    ; ax = LBA / SectorsPerTrack
                                                ; dx = LBA % SectorsPerTrack

            inc dx                              ; dx = (LBA % SectorsPerTrack + 1) = sector
            mov cx, dx                          ; cx = sector

            xor dx, dx
            div word [bdb_heads]                ; ax = (LBA / SectorsPerTrack) / Heads = cylinder
                                                ; dx = (LBA / SectorsPerTrack) % Heads = head
            mov dh, dl                          ; dh = head
            mov ch, al                          ; ch = cylinder (lower 8 bits)
            shl ah, 6
            or cl, ah                           ; put upper 2 bits of cylinder in CL

            pop ax
            pop dx
            mov dl, al                          ; restore DL
            ;pop ax

            ret


;
; Reads sectors from a disk
; Parameters:
;   - ax: LBA address
;   - cl: number of sectors to read (up to 128)
;   - dl: drive number
;   - es:bx memory address where to store read data
;
disk_read:

    push ax                                         ; save registers to modify
    push bx
    push dx
    push di

    push cx                                         ; temporarily save CL (number of sectors to read)
    call lba_to_chs                                 ; compute CHS
    ; Goes to here perfectly
    pop ax                                          ; AL = number of sectors to read

    mov ah, 0x02
    mov di, 3                                       ; retry count

.retry:
    pusha                                           ; save all registers, unknown modification
    stc                                             ; set carry flag, some BIOS'es don't set it
    int 0x13                                        ; carry flag cleared = success
    jnc .done                                       ; jump if carry not set

    ; read failed
    popa
    call disk_reset

    dec di
    test di, di
    jnz .retry

.fail:
    ; after all attempts are exhausted
    mov ah, 0x0E
    mov al, 'T'
    int 0x10
    jmp floppy_error

.done:
    mov ah, 0x0E
    mov al, 'R'
    int 0x10
    popa

    push di                                         ; restore registers modified
    push dx
    push cx
    push bx
    push ax
    ret

;
; Reset disk controller
; Parameters:
;   - dl: drive number
disk_reset:
    pusha
    mov ah, 0
    stc
    int 0x13
    jc floppy_error
    popa
    ret

[bits 32]
BEGIN_32_BIT:
    mov ah, 0x0E
    mov al, '!'
    int 0x10
    ;jmp KERNEL_OFFSET ; Call the kernel
    jmp 0x7E00 ; Call the kernel

newline db 0x0A
;BOOT_DRIVE db 0
;KERNEL_OFFSET equ 0x1000
MSG_READ_SUCCESS: db "Reading from disk: Success", 0
MSG_READ_FAILED: db 'Read from disk failed!', 0

times 510-($-$$) db 0 ; Pad the rest of the sector with zeros to make it 512 bytes
dw 0xAA55 ; Boot signature, magic number

