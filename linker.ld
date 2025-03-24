OUTPUT_FORMAT(binary)
ENTRY(_start)
SECTIONS
{
    . = 0x7C00;
    .text : AT(0x7C00)
    {
        *(.text)
    }
    .data : AT(0x1000)
    {
        *(.data)
    }
    .bss : AT(0x8000)
    {
        *(.bss)
    }
}
