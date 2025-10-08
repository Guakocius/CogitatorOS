disk_load:

    pusha
    push dx

    ; Debug: print 'D' before disk read
    mov ah, 0x0E
    mov al, 'D'
    int 0x10

    mov ah, 0x02            ; Read Sectors
    mov al, dh              ; Number of sectors to read provided by caller in DH
    mov [SECTORS_TO_READ], al
    mov cl, 0x02            ; Start at sector 2
    mov ch, 0x00            ; Cylinder 0
    mov dh, 0x00            ; Head 0
    ; [es:bx] destination set by caller
    int 0x13

    jc disk_error

    ; Verify we read the requested number of sectors
    cmp al, [SECTORS_TO_READ]
    jne sectors_error

    pop dx

    ; Optional: print '.' on success
    mov ah, 0x0E
    mov al, '.'
    int 0x10

    popa
    ret

disk_error:
    ; Print 'E' for disk error
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    jmp disk_loop

sectors_error:
    ; Print 'S' for sector mismatch error
    mov ah, 0x0E
    mov al, 'S'
    int 0x10
    jmp disk_loop

disk_loop:
    jmp $

SECTORS_TO_READ db 0
