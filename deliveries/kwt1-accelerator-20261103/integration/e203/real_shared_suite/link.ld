OUTPUT_ARCH(riscv)
ENTRY(_start)
PHDRS {
  code PT_LOAD FLAGS(5);
  data PT_LOAD FLAGS(6);
}
SECTIONS {
  . = 0x80000000;
  .entry : { KEEP(*(.text.entry)) } :code
  ASSERT(SIZEOF(.entry) <= 0x86, "Entry overlaps TB termination PC")
  . = 0x80000086;
  .test_end : { KEEP(*(.text.test_end)) } :code
  ASSERT(SIZEOF(.test_end) == 2, "Expected 2-byte termination loop")
  . = 0x80000100;
  .text : { *(.text.boot) *(.text .text.*) } :code
  .rodata : { *(.rodata .rodata.*) } :code
  . = ALIGN(4);
  .data : { *(.data .data.* .sdata .sdata.*) } :data
  .bss (NOLOAD) : {
    . = ALIGN(4);
    __bss_start = .;
    *(.bss .bss.* .sbss .sbss.* COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } :data
  __stack_top = 0x80001000;
  ASSERT(__bss_end <= 0x80000c00, "Need at least 1 KiB stack within first 4 KiB ITCM")
  /DISCARD/ : { *(.comment .note.* .eh_frame .eh_frame.*) }
}
