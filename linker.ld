OUTPUT_FORMAT(binary)
ENTRY(kernel_main)
SECTIONS
{
    . = 0x7E00;
    .text : {
        *(.multiboot)
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }
    .data : {
        *(.data*)
    }
    .bss : {
        *(.bss)
        *(COMMON)
    }
}
