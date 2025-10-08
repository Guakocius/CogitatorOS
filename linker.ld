OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
    /* Load the 32-bit kernel at physical 0x1000 as the bootloader expects */
    . = 0x1000;
    .text ALIGN(4) :
    {
        *(.multiboot)
        *(.text*)
    }
    .rodata ALIGN(4) : { *(.rodata*) }
    .data ALIGN(4)   : { *(.data*) }
    .bss  ALIGN(4)   : { *(.bss*) *(COMMON) }
}
