disk_load:
    pusha
    push dx

    mov ah, 0x02 ; Read sectors
    mov al, dh   ; Number of sectors to read
    mov cl, 0x02 ; Start at sector 2
                 ; Sector 1 is the boot sector
    mov ch, 0x00 ; Cylinder 0
    mov dh, 0x00 ; Head 0
    ;mov dl, [BOOT_DRIVE] ; Drive

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh

    jne sectors_error

    popa
    ret

disk_error:
    mov ah, '1' ; Error Code
    jmp error_loop

sectors_error:
    mov ah, '2' ; Error Code
    jmp error_loop

error_loop:
    mov dh, ah
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    mov al, 'r'
    int 0x10
    int 0x10
    mov al, 0x20 ; Space
    int 0x10
    mov al, dh ; Print Error Code
    int 0x10

    jmp $
    