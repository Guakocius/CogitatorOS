segment readable executable
global set_video_mode
global draw_px

; Set video mode to 320x200 256-color mode (mode 0x13)
set_video_mode:
    mov rax, 0x0013 ; Set video mode to 320x200 256-color mode
    int 0x10 ; Call the BIOS
    ret

; Draw a pixel at the specified coordinates with the specified color
; Input
;   - cx: x-coordinate
;   - dx: y-coordinate
;   - al: color
draw_px:
    mov ah, 0x0C ; BIOS plot pixel function
    int 0x10 ; Call the BIOS
    ret
