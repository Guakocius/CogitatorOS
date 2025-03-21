;;; gdt_start and gdt_end labels are used to compute size

gdt_start:
    dq 0x0

gdt_code:
    dw 0xffff ; Limit
    dw 0x0 ; Base bits 0 - 15
    db 0x0 ; Base bits 16 - 23
    db 10011010b ; Access byte
    db 11001111b ; Granularity
    db 0x0 ; Base bits 24 - 31

gdt_data:
    dw 0xffff ; Limit
    dw 0x0 ; Base bits 0 - 15
    db 0x0 ; Base bits 16 - 23
    db 10010010b ; Access byte
    db 11001111b ; Granularity
    db 0x0 ; Base bits 24 - 31

gdt_end:

    gdt_descriptor:
        dw gdt_end - gdt_start - 1 ; size (16 bit)
        dd gdt_start ; address (32 bit)

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start