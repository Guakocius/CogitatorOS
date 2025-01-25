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