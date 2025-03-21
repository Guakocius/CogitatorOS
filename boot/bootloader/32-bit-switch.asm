[bits 16]
switch_to_32bit:
    cli
    lgdt [gdt_descriptor] ; Load GDT Descriptor
    mov eax, cr0
    or eax, 0x1 ; enable protected mode
    mov cr0, eax
    jmp CODE_SEG:init_32_bit

[bits 32]
init_32_bit:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call BEGIN_32_BIT ; move back to mbr.asm