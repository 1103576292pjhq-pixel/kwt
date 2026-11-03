    .option norelax
    .option norvc
    .section .text.entry,"ax",@progbits
    .globl _start
    .type _start,@function
_start:
    j _boot
    .size _start, .-_start

    /* Match existing tb_top PC_WRITE_TOHOST, without changing its simv. */
    .section .text.test_end,"ax",@progbits
    .option push
    .option rvc
    .balign 2
    .globl test_end
    .type test_end,@function
test_end:
    c.j test_end
    .size test_end, .-test_end
    .option pop

    .section .text.boot,"ax",@progbits
    .balign 4
    .globl _boot
    .type _boot,@function
_boot:
    la sp, __stack_top
    csrw mie, zero
    csrci mstatus, 8
    la t0, trap_entry
    csrw mtvec, t0
    la t0, __bss_start
    la t1, __bss_end
1:
    bgeu t0, t1, 2f
    sw zero, 0(t0)
    addi t0, t0, 4
    j 1b
2:
    call main
    /* Existing TB treats x3=1 as pass; compiler uses no gp-relative storage. */
    mv gp, a0
    fence iorw, iorw
    j test_end
    .size _boot, .-_boot

    .balign 4
    .globl trap_entry
    .type trap_entry,@function
trap_entry:
    csrr a1, mcause
    csrr a2, mepc
    csrr a3, mtval
    li gp, 0xe0
    j test_end
    .size trap_entry, .-trap_entry
