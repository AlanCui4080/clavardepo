ENTRY(_entry)
MEMORY
{
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 144K
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 512K
}
SECTIONS
{
    _start_text = .;
    .text :
    {
        KEEP(*(.vector_table))
        . = ALIGN(4);
        *(.text)
    } >FLASH
    _end_text = .;

    _start_rodata = .;
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
    } >FLASH
    _end_rodata = .;

    _load_data = LOADADDR(.data);
    _start_data = .;
    .data :
    {
        . = ALIGN(4);
        *(.data)
        *(.data*)
    } >RAM AT>FLASH
    _end_data = .;

    _start_bss = .;
    .bss :
    {
        . = ALIGN(4);
        *(.bss)
        *(.bss*)
    } >RAM
    _end_bss = .;

    .avail :
    {
        . = ALIGN(16);

        _start_avail = .;
        _total_avail = ORIGIN(RAM) + LENGTH(RAM) - _start_avail;
        _end_avail = ORIGIN(RAM) + LENGTH(RAM);
        _high_stack = ORIGIN(RAM) + LENGTH(RAM);
    } >RAM
}
