; BIOS
org 0x7C00 ; BIOS loads the boot sector into memory location 0x7c00

start:
    ; Set up the stack
    cli
    xor ax,  ax ; Set AX to 0
    mov ss, ax ; Stack starts at 0x7C0:0x0000
    mov sp, 0x7C00 ; Stack starts at 0x7C00:0x0000
    sti ; Enable interrupts

    ; Print a message
    mov si, msg
    call print_string

    ; Wait for a key press
    call wait_for_key

    ; Check if F2 is pressed
    cmp al, 0x3C; F2 key code
    je enter_bios

enter_bios:
    ; Enter BIOS
    mov si, bios_msg
    call print_string
    jmp $

print_string:
    lodsb ; Load the next byte from SI into AL
    or al, al ; Set the zero flag if AL is 0
    jz .done ; Jump if AL is 0
    mov ah, 0x0E ; BIOS teletype function
    int 0x10 ; Call the BIOS
    jmp print_string
    .done:
        ret

wait_for_key:
    xor ah, ah ; BIOS keyboard function
    int 0x16 ; Call the BIOS
    ret

msg db "Press F2 to enter BIOS setup...", 0
bios_msg db "Entering BIOS setup...", 0

times 510-($-$$) db 0 ; Fill the rest of the boot sector with zeros
dw 0xAA55 ; Boot signature