#ifndef KWT1_FFN1_DRIVER_H
#define KWT1_FFN1_DRIVER_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KWT1_MMIO_BASE UINT32_C(0x11000000)
#define KWT1_ID_VALUE UINT32_C(0x4b575431)
#define KWT1_DOT_LENGTH UINT32_C(64)

enum kwt1_register {
    KWT1_REG_ID = 0x00,
    KWT1_REG_STATUS = 0x04,
    KWT1_REG_COMMAND = 0x08,
    KWT1_REG_ERROR = 0x0c,
    KWT1_REG_SHIFT = 0x10,
    KWT1_REG_LOAD_KIND = 0x14,
    KWT1_REG_LOAD_ADDR = 0x18,
    KWT1_REG_LOAD_LO = 0x1c,
    KWT1_REG_LOAD_HI = 0x20,
    KWT1_REG_LOAD_COMMIT = 0x24,
    KWT1_REG_ROW_INDEX = 0x28,
    KWT1_REG_ROW_ADDR = 0x2c,
    KWT1_REG_ROW_DATA = 0x30,
    KWT1_REG_ROW_FLAGS = 0x34,
    KWT1_REG_ROW_ACK = 0x38,
    KWT1_REG_GEOMETRY = 0x3c,
    KWT1_REG_DOT_LENGTH = 0x40
};

enum kwt1_status_bit {
    KWT1_STATUS_BUSY = 1,
    KWT1_STATUS_LOADED = 2,
    KWT1_STATUS_ROW_READY = 4,
    KWT1_STATUS_DONE = 8,
    KWT1_STATUS_ERROR = 16
};

enum kwt1_result {
    KWT1_OK = 0,
    KWT1_ERR_ARGUMENT = -1,
    KWT1_ERR_IO = -2,
    KWT1_ERR_ID = -3,
    KWT1_ERR_GEOMETRY = -4,
    KWT1_ERR_BUSY = -5,
    KWT1_ERR_CORE = -6,
    KWT1_ERR_TIMEOUT = -7,
    KWT1_ERR_PROTOCOL = -8
};

/* All offsets are relative to KWT1_MMIO_BASE, never absolute addresses.
 * A callback returns 0 on success and nonzero on any bus/access failure.
 * read32 must fill *value only after the read response has been consumed.
 * write32 must consume its write response before returning. The callbacks
 * must themselves complete in bounded time; poll_limit cannot interrupt them.
 */
typedef struct kwt1_io {
    void *context;
    int (*read32)(void *context, uint32_t offset, uint32_t *value);
    int (*write32)(void *context, uint32_t offset, uint32_t value);
} kwt1_io;

/* Blocking, single-owner driver. Requires the accelerator to be idle and
 * free of sticky errors on entry. Does not clear errors, reset hardware,
 * allocate memory, or calculate expected matrix results.
 *
 * Caller owns suitably aligned, non-overlapping arrays valid for the entire
 * call: x[m*64], w_pack[n*64] (column-major packed as [n][64]), bias[n],
 * y[m*n], and optional flags[m*n]. m/n must match hardware GEOMETRY exactly.
 * All bias values must be signed 48-bit. shift is 0..47. poll_limit > 0 is
 * the maximum STATUS reads in each loaded/row/done wait, not a cycle count.
 * A row is ACKed only after its full data and valid flags have been copied.
 * flags stores the hardware ROW_FLAGS byte (bit0 overflow, bit1 saturated,
 * bit2 valid); saturation/overflow are reported data, not transport errors.
 *
 * On error, already copied output elements may remain, and the current job
 * may still be busy. The caller must recover/reset explicitly before retry.
 * The function never ACKs an incompletely read row or retries failed I/O.
 */
int kwt1_run(const kwt1_io *io, uint32_t m, uint32_t n,
             const int16_t *x, const int16_t *w_pack, const int64_t *bias,
             uint32_t shift, int32_t *y, uint8_t *flags, uint32_t poll_limit);

#ifdef __cplusplus
}
#endif

#endif
