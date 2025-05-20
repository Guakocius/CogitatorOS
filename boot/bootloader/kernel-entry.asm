[bits 32]
extern _main
global _start

_start:
    call _main
    jmp $

kernel_entry:
    jmp _start
