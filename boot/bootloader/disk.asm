disk_load:

    pusha
    push dx

    mov ah, 0x02 ; Read Sectors
    mov al, dh ; Number of Sectors to Read (0x02 .. 0x80)
    mov cl, 0x02 ; sector (0x01 .. 0x11)

    mov ch, 0x00 ; cylinder (0x0 .. 0x3FF, upper two bits in 'cl'
    ; dl <- drive number. Our caller sets it as a parameter and gets it from BIOS
    ; (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2))
    mov dh, 0x00 ; head number (0x0 .. 0xF)
    ; [es:bx] <- pointer to buffer where the data will be stored
    ; caller sets it up for us, and it is actually the standard location for int 13h
    int 0x13
    ;call switch_to_32bit
    ;[bits 32]

    jc disk_error

    pop dx
    cmp al, dh ; Check if the number of sectors read is equal to the number of requested
    jne sectors_error

    ; If no errors, print '1'
    mov ah, 0x0E
    mov al, '1'
    int 0x10

    popa
    ret

disk_error:
    mov bx, DISK_ERROR
    call print
    call print_nl
    mov dh, ah ; ah = error code, dl = disk drive that dropped the error
    call print_hex
    jmp disk_loop

sectors_error:
    mov bx, SECTORS_ERROR
    call print

disk_loop:
    jmp $

print:
    pusha

print_nl:
    pusha

    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10

    popa
    ret

print_hex:
    pusha

    mov cx, 0 ; counter

DISK_ERROR db "Disk read error", 0
SECTORS_ERROR db "Incorrect numbers of sectors read", 0
