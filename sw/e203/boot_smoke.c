#include <stdint.h>

/* Firmware owns the mailbox; the testbench only supplies mode at offset 0x20. */
static volatile uint32_t zero_bss[17];
static volatile uint32_t initialized_data = 0x1234abcdu;
static uint32_t exercise_stack(uint32_t seed) {
    volatile uint32_t scratch[13];
    uint32_t result = seed;
    for (uint32_t i=0; i<13; ++i) scratch[i] = i * 7u + seed;
    for (uint32_t i=0; i<13; ++i) result ^= scratch[i];
    return result;
}

int main(void) {
    volatile uint32_t *shared=(volatile uint32_t *)(uintptr_t)0xa0000000u;
    for (uint32_t i=0; i<17; ++i) if (zero_bss[i] != 0) return 1;
    if (initialized_data != 0x1234abcdu) return 2;
    if (exercise_stack(3) != 0x14u) return 3;
    initialized_data ^= 0xffffffffu;
    if (initialized_data != 0xedcb5432u) return 4;
    /* AMO plus compressed and multiply/divide are genuine RV32 code paths. */
    uint32_t old;
    zero_bss[0]=9;
    uint32_t add=5;
    __asm__ volatile("amoadd.w %0,%2,(%1)" : "=r"(old) : "r"(&zero_bss[0]), "r"(add) : "memory");
    if (old != 9 || zero_bss[0] != 14) return 5;
    volatile uint32_t x=12345u, y=17u;
    if (x*y != 209865u || x/y != 726u || x%y != 3u) return 6;
    shared[24]=0x10203040u;
    volatile uint8_t *bytes=(volatile uint8_t *)&shared[24];
    bytes[1]=0x5au;
    if (shared[24] != 0x10205a40u) return 7;
    shared[25]=exercise_stack(3);
    if (shared[8] == 1u) __asm__ volatile(".word 0xffffffff");
    return 0;
}
