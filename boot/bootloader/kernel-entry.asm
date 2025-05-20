[bits 32]
%include "kernel/arch/x86/kernel.c"
[extern main]
kernel_entry:
    call main
jmp $