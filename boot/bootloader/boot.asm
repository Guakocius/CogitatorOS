org 0x7C00 ; BIOS loads the boot sector into memory location 0x7c00

mov ax, 0x7C0 ; Set up the stack
mov ss, ax ; Stack starts at 0x7C0:0x0000
mov sp, 0x0200 ; Stack starts at 0x7C00:0x0200

; Load Bootloader Stage 2: Initializing the system
mov si, msg ; Print message
call print_string ; Call print_string function

; Load BIOS code from disk
mov bx, 0x8000 ; Load BIOS code to 0x8000
mov dh, 0x01 ; Load 1 sector
mov dl, 0x80 ; Load from disk 0
mov ch, 0x00 ; Cylinder 0
mov cl, 0x02 ; Sector 2
mov ah, 0x02 ; Read disk sectors
int 0x13 ; Call BIOS

jc disk_error ; Jump to disk_error if error

; Jump to BIOS code
jmp 0x8000:0x0000 ; Jump to BIOS code, segment 0x8000, offset 0x0000

disk_error:
    mov si, disk_error_msg ; Print error message
    call print_string ; Call print_string function
    hlt ; Halt the system

msg db "Loading Bootloader Stage 2...", 0 ; Message to print
disk_error_msg db "Error loading BIOS code from disk", 0 ; Error message

print_string: ; Function to print a string
    ; Print characters until we reach the null-terminator
    mov ah, 0x0E ; BIOS teletype function
    .loop:
        lodsb ; Load the next byte from SI into AL
        cmp al, 0 ; Check if the byte is null
        je .done ; If null, we're done
        int 0x10 ; Otherwise, print the character
        jmp .loop ; Repeat until null
    .done:
        ret ; Return from the function
times 510-($-$$) db 0 ; Pad the rest of the sector with zeros to make it 512 bytes
dw 0xAA55 ; Boot signature
