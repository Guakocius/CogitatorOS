[bits 32]
extern _main
global kernel_entry
kernel_entry:
    call _main
    jmp $