#include <assert.h>
#include <stdio.h>
#include <string.h>

extern unsigned int kwt_mmio_test(void);
static unsigned int regs[18], mode, reads, writes;

unsigned int kwt_read32(unsigned int offset)
{
    ++reads;
    assert((offset & 3u) == 0u && offset <= 0x44u);
    if (mode == 1u) return 0u; /* Original zero-response placeholder. */
    if (offset == 0u) return mode == 2u ? 0x11u : 1u;
    if (offset == 0x1cu) return mode == 3u ? 1u : 0u;
    if (mode == 4u && offset == 4u) return regs[1] ^ 1u;
    if (mode == 6u) return regs[1]; /* All registers incorrectly alias. */
    return regs[offset / 4u];
}

void kwt_write32(unsigned int offset, unsigned int value)
{
    ++writes;
    /* Reject accidental commands, ACK, ABORT or status writes in this test. */
    assert(offset == 4u || offset == 8u || offset == 12u || offset == 16u ||
           offset == 20u || offset == 52u || offset == 56u || offset == 60u);
    if (mode == 5u) return; /* Writes silently lost. */
    regs[mode == 6u ? 1u : offset / 4u] = value;
}

int main(void)
{
    unsigned int result;
    for (mode = 0u; mode < 7u; ++mode) {
        memset(regs, 0, sizeof(regs));
        reads = writes = 0;
        result = kwt_mmio_test();
        if (mode == 0u) {
            assert(result == 1u);
            assert(reads == 28u && writes == 24u);
            for (unsigned int i = 0u; i < 18u; ++i) assert(regs[i] == 0u);
        } else {
            assert(result != 1u);
        }
    }
    puts("PASS MMIO_TEST_LOGIC scenarios=7 valid_reads=28 valid_writes=24");
    return 0;
}
