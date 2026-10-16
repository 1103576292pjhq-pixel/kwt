OUTPUT_ARCH(riscv)
ENTRY(_start)
MEMORY {
  ITCM (rxw) : ORIGIN = 0x80000000, LENGTH = 64K
  DTCM (rw)  : ORIGIN = 0x90000000, LENGTH = 64K
}
SECTIONS {
  .text : { KEEP(*(.text.init)) *(.text .text.*) } > ITCM
  .rodata : { *(.rodata .rodata.*) } > ITCM
  .data : ALIGN(4) {
    __data_start = .;
    *(.data .data.*)
    PROVIDE(__global_pointer$ = . + 0x800);
    *(.sdata .sdata.*)
    . = ALIGN(4);
    __data_end = .;
  } > DTCM AT> ITCM
  __data_load = LOADADDR(.data);
  .bss (NOLOAD) : ALIGN(4) {
    __bss_start = .;
    *(.sbss .sbss.*) *(.bss .bss.*) *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } > DTCM
  __stack_top = ORIGIN(DTCM) + LENGTH(DTCM);
  ASSERT(__bss_end + 4096 <= __stack_top, "DTCM leaves less than 4KiB stack")
  /DISCARD/ : { *(.comment) *(.eh_frame*) }
}
