#include <stdint.h>
#include "kwt_mmio.h"

unsigned int kwt_read32(unsigned int offset)
{
    unsigned int value = *(volatile unsigned int *)(uintptr_t)(KWT_BASE + offset);
    __asm__ volatile ("fence iorw, iorw" ::: "memory");
    return value;
}

void kwt_write32(unsigned int offset, unsigned int value)
{
    *(volatile unsigned int *)(uintptr_t)(KWT_BASE + offset) = value;
    __asm__ volatile ("fence iorw, iorw" ::: "memory");
}

int main(void)
{
    return (int)kwt_mmio_test();
}
