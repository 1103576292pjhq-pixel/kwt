#include "fixture.h"

/* Integer encodings in the frozen Q12/Q16/Q28 contract; no floats or arrays. */
int32_t fixture_x(uint32_t row, uint32_t k)
{
    return (((int32_t)row - 49)*8 + 2*(int32_t)k - 63)*8;
}

int32_t fixture_w(uint32_t k, uint32_t column)
{
    if (column == 0) return 32767;
    if (column == 1) return -32768;
    if (column < 8) return 0;
    return (((int32_t)column - 128)*8 + (int32_t)k - 32)*8;
}

int32_t fixture_bias(uint32_t column)
{
    /* Explicit positive/negative odd/even half-way cases in columns 2..7. */
    if (column < 2) return 0;
    if (column < 8) {
        int32_t value = column < 4 ? 98304 : column < 6 ? 32768 : 163840;
        return column & 1u ? -value : value;
    }
    return ((int32_t)column - 128)*1024 + 32736;
}

uint32_t fixture_convert(int64_t raw, uint32_t last)
{
    /* Legal K64 inputs cannot overflow acc40. This fixture is in that domain. */
    uint64_t magnitude = raw < 0 ? (uint64_t)(-raw) : (uint64_t)raw;
    uint32_t q = (uint32_t)(magnitude >> 16);
    uint32_t rem = (uint32_t)magnitude & 65535u;
    if (rem > 32768u || (rem == 32768u && (q & 1u))) ++q;
    int32_t rounded = raw < 0 ? -(int32_t)q : (int32_t)q;
    uint32_t flags = last ? 4u : 0u;
    if (rounded > 32767) { rounded = 32767; flags |= 2u; }
    if (rounded < -32768) { rounded = -32768; flags |= 2u; }
    return ((uint32_t)rounded & 65535u) | (flags << 16);
}

uint32_t fixture_expected(uint32_t row, uint32_t column)
{
    int32_t a = ((int32_t)row - 49)*8 - 63;
    int64_t raw;
    if (column < 2) {
        /* sum_k X = 8*(64*a + 2*sum k); sum k = 2016. */
        raw = (int64_t)(8*(64*a + 4032))*fixture_w(0, column);
    } else if (column < 8) {
        raw = 0;
    } else {
        int32_t b = ((int32_t)column - 128)*8 - 32;
        /* sum (8*(a+2k))*(8*(b+k)); sum k^2 = 85344. */
        raw = (int64_t)(64*a*b + (a+2*b)*2016 + 170688)*64;
    }
    raw += fixture_bias(column);
    return fixture_convert(raw, row == 98 && column == 255);
}
