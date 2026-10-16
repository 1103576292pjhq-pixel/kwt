/* Real RV32 firmware: all arithmetic results are read from the accelerator.
 * Shared SRAM contains inputs only; expected outputs never enter this image.
 */
#include "ffn1_driver.h"

static int mmio_read(void *context, uint32_t offset, uint32_t *value)
{
    (void)context;
    __asm__ volatile("fence iorw,iorw" ::: "memory");
    *value = *(volatile uint32_t *)(uintptr_t)(KWT1_MMIO_BASE + offset);
    __asm__ volatile("fence iorw,iorw" ::: "memory");
    return 0;
}

static int mmio_write(void *context, uint32_t offset, uint32_t value)
{
    (void)context;
    __asm__ volatile("fence iorw,iorw" ::: "memory");
    *(volatile uint32_t *)(uintptr_t)(KWT1_MMIO_BASE + offset) = value;
    __asm__ volatile("fence iorw,iorw" ::: "memory");
    return 0;
}

int main(void)
{
    volatile const uint32_t *config = (volatile const uint32_t *)(uintptr_t)0xa0000100;
    volatile uint32_t *phase = (volatile uint32_t *)(uintptr_t)0xa0000040;
    static const kwt1_io io = {0, mmio_read, mmio_write};
    const int16_t *x = (const int16_t *)(uintptr_t)0xa0001000;
    const int16_t *w = (const int16_t *)(uintptr_t)0xa0005000;
    const int64_t *bias = (const int64_t *)(uintptr_t)0xa000d000;
    int32_t *y = (int32_t *)(uintptr_t)0xa0010000;
    uint8_t *flags = (uint8_t *)(uintptr_t)0xa0030000;
    *phase = 1;
    int result = kwt1_run(&io, config[0], config[1], x, w, bias,
                           config[2], y, flags, 1000000);
    *phase = result == KWT1_OK ? 2 : 0xffffffffu;
    return result;
}
