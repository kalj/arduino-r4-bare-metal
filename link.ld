MEMORY {
  /* pflash(rx) : ORIGIN = 0x00000000, LENGTH = 256k */
  pflash(rx) : ORIGIN = 0x00004000, LENGTH = 256k
  sram(rwx)  : ORIGIN = 0x20000000, LENGTH = 16k
  dflash(r)  : ORIGIN = 0x40100000, LENGTH = 8k
}

_STACK_END = ORIGIN(sram) + LENGTH(sram); /* stack points to end of sram */

SECTIONS {
  .vectors : { KEEP(*(.vectors)) } > pflash
  .text    : { *(.text*) } > pflash
  .rodata  : { *(.rodata*) } > pflash

  .data : {
    _DATA_START = .;
    /* *(.first_data) */
    *(.data SORT(.data.*))
    _DATA_END = .;
   } > sram AT > pflash
   /* } > sram AT > dflash */

  _DATA_LOAD_ADDRESS = LOADADDR(.data);

  .bss : {
    _BSS_START = .;
    *(.bss SORT(.bss.*) COMMON)
    _BSS_END = .;
   } > sram
}
