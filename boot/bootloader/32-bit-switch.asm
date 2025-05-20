[bits 16]


global init_32_bit
global switch_to_32bit

%include "./boot/bootloader/kernel-entry.asm"
%include "./boot/bootloader/gdt.asm"


;extern DATA_SEG
;extern CODE_SEG
;extern gdt_descriptor
;extern kernel_entry



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

    mov ebp, 0x9000
    mov esp, ebp

    call kernel_entry