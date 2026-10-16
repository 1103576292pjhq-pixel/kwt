/* Freestanding RV32IMAC startup. No SDK or libc dependency. */
.section .text.init,"ax",@progbits
.balign 4
.globl _start
.type _start,@function
_start:
  .option push
  .option norelax
  la gp, __global_pointer$
  .option pop
  la sp, __stack_top
  la t0, trap_entry
  csrw mtvec, t0
  csrw mie, zero
  csrci mstatus, 8
  la t0, __data_load
  la t1, __data_start
  la t2, __data_end
1:
  bgeu t1, t2, 2f
  lw t3, 0(t0)
  sw t3, 0(t1)
  addi t0, t0, 4
  addi t1, t1, 4
  j 1b
2:
  la t0, __bss_start
  la t1, __bss_end
3:
  bgeu t0, t1, 4f
  sw zero, 0(t0)
  addi t0, t0, 4
  j 3b
4:
  call main
  /* A returning main always publishes completion, including a failure code. */
  li t0, 0xa0000000
  sw a0, 4(t0)
  csrr t1, mcycle
  sw t1, 16(t0)
  fence rw,rw
  li t1, 0x424f4f54
  sw t1, 0(t0)
5:
  j 5b
.size _start, .-_start

.balign 4
.type trap_entry,@function
trap_entry:
  li t0, 0xa0000000
  csrr t1, mcause
  sw t1, 8(t0)
  csrr t1, mepc
  sw t1, 12(t0)
  li t1, -1
  sw t1, 4(t0)
  csrr t1, mcycle
  sw t1, 16(t0)
  fence rw,rw
  li t1, 0x54524150
  sw t1, 0(t0)
6:
  j 6b
.size trap_entry, .-trap_entry
