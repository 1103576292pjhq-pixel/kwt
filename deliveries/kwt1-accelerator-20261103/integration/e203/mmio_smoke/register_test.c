#include "kwt_mmio.h"

/* Kept in ITCM bss for diagnosis; these do not require shared SRAM. */
volatile unsigned int test_phase, test_last_offset, test_expected, test_observed;

static const struct {
    unsigned int offset;
    unsigned int mask;
} fields[] = {
    {KWT_TASK, 0xffffffffu}, {KWT_LAYER, 0x0000000fu},
    {KWT_TILE, 0x0000000fu}, {KWT_INDEX, 0x00001fffu},
    {KWT_DATA, 0xffffffffu}, {KWT_ACK_TASK, 0xffffffffu},
    {KWT_ACK_SEQ, 0x000001ffu}, {KWT_ACK_COUNT, 0x0000007fu}
};

static unsigned int check(unsigned int offset, unsigned int expected)
{
    test_last_offset = offset;
    test_expected = expected;
    test_observed = kwt_read32(offset);
    return test_observed == expected;
}

static unsigned int pattern(unsigned int pass, unsigned int index)
{
    unsigned int value = pass == 0u ? 0xffffffffu :
        (pass == 1u ? (0x13579bdfu ^ (0x01020408u * (index + 1u))) : 0u);
    return value & fields[index].mask;
}

unsigned int kwt_mmio_test(void)
{
    test_phase = 1u;
    if (!check(KWT_STATUS, 1u)) return 0x10u;
    if (!check(KWT_ERROR, 0u)) return 0x11u;

    for (unsigned int pass = 0u; pass < 3u; ++pass) {
        test_phase = 2u + pass;
        /* Write every field before reading any back, to detect address aliasing. */
        for (unsigned int i = 0u; i < 8u; ++i)
            kwt_write32(fields[i].offset, pattern(pass, i));
        for (unsigned int i = 0u; i < 8u; ++i)
            if (!check(fields[i].offset, pattern(pass, i))) return 0x20u + i;
    }
    test_phase = 5u;
    if (!check(KWT_STATUS, 1u)) return 0x40u;
    if (!check(KWT_ERROR, 0u)) return 0x41u;
    test_phase = 6u;
    return 1u;
}
