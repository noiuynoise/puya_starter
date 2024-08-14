MEMORY
{
  rom      (rx)  : ORIGIN = 0x08000000, LENGTH = 64k
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 8k
}

STACK_SIZE = 1k;

/* Section Definitions */
SECTIONS
{
    .text :
    {
        KEEP(*(.vectors))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _preinit_array_start = .;
        KEEP (*(.preinit_array));
        _preinit_array_end = .;
        . = ALIGN(4);
        _init_array_start = .;
        KEEP (*(SORT(.init_array.*)));
        KEEP (*(.init_array));
        _init_array_end = .;
        _etext = .;
    } > rom

    .bss (NOLOAD) :
    {
        _sbss = .;
        *(.bss*)
        _ebss = .;
    } > ram

    .data :
    {
        _sdata = .;
        *(.data*);
        *(.ramfunc*);
        _edata = .;
    } > ram AT >rom

    /* heap section */
    .heap (NOLOAD):
    {
        . = ALIGN(8);
        end = .;
    } > ram

    /* stack end is end of ram */
    _estack = ORIGIN(ram) + LENGTH(ram);
}