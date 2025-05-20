OUTPUT_FORMAT(binary)
ENTRY(kernel_entry)
SECTIONS
{
    . = 0x7E00;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}
