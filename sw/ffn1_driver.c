#include "ffn1_driver.h"

static int read_register(const kwt1_io *io, uint32_t offset, uint32_t *value)
{
    return io->read32(io->context, offset, value) == 0 ? KWT1_OK : KWT1_ERR_IO;
}

static int write_register(const kwt1_io *io, uint32_t offset, uint32_t value)
{
    return io->write32(io->context, offset, value) == 0 ? KWT1_OK : KWT1_ERR_IO;
}

static int read_status(const kwt1_io *io, uint32_t *status)
{
    int rc = read_register(io, KWT1_REG_STATUS, status);
    if (rc != KWT1_OK) {
        return rc;
    }
    if ((*status & KWT1_STATUS_ERROR) != 0) {
        return KWT1_ERR_CORE;
    }
    if ((*status & ~UINT32_C(31)) != 0) {
        return KWT1_ERR_PROTOCOL;
    }
    return KWT1_OK;
}

static int check_error(const kwt1_io *io)
{
    uint32_t error;
    int rc = read_register(io, KWT1_REG_ERROR, &error);
    if (rc != KWT1_OK) {
        return rc;
    }
    return error == 0 ? KWT1_OK : KWT1_ERR_CORE;
}

enum wait_kind { WAIT_LOADED, WAIT_ROW, WAIT_DONE };

static int wait_status(const kwt1_io *io, enum wait_kind kind, uint32_t limit)
{
    for (uint32_t poll = 0; poll < limit; poll++) {
        uint32_t status;
        int rc = read_status(io, &status);
        if (rc != KWT1_OK) {
            return rc;
        }
        if (kind == WAIT_LOADED) {
            if ((status & (KWT1_STATUS_BUSY | KWT1_STATUS_ROW_READY | KWT1_STATUS_DONE)) != 0) {
                return KWT1_ERR_PROTOCOL;
            }
            if ((status & KWT1_STATUS_LOADED) != 0) {
                return KWT1_OK;
            }
        } else if (kind == WAIT_ROW) {
            if ((status & (KWT1_STATUS_DONE | KWT1_STATUS_LOADED)) != 0 ||
                (status & KWT1_STATUS_BUSY) == 0) {
                return KWT1_ERR_PROTOCOL;
            }
            if ((status & KWT1_STATUS_ROW_READY) != 0) {
                return KWT1_OK;
            }
        } else {
            if ((status & (KWT1_STATUS_ROW_READY | KWT1_STATUS_LOADED)) != 0) {
                return KWT1_ERR_PROTOCOL;
            }
            if ((status & KWT1_STATUS_DONE) != 0) {
                return (status & KWT1_STATUS_BUSY) == 0 ? KWT1_OK : KWT1_ERR_PROTOCOL;
            }
        }
    }
    return KWT1_ERR_TIMEOUT;
}

static int load_bank(const kwt1_io *io, uint32_t kind, uint32_t count,
                     const int16_t *words, const int64_t *bias)
{
    int rc = write_register(io, KWT1_REG_LOAD_KIND, kind);
    if (rc != KWT1_OK) {
        return rc;
    }
    for (uint32_t address = 0; address < count; address++) {
        uint32_t lo;
        rc = write_register(io, KWT1_REG_LOAD_ADDR, address);
        if (rc != KWT1_OK) {
            return rc;
        }
        if (kind == 2) {
            /* Conversion to unsigned is defined modulo 2^64, including the
             * signed48 minimum. No right shift of a negative signed value. */
            uint64_t bits = (uint64_t)bias[address];
            lo = (uint32_t)bits;
            rc = write_register(io, KWT1_REG_LOAD_LO, lo);
            if (rc != KWT1_OK) {
                return rc;
            }
            rc = write_register(io, KWT1_REG_LOAD_HI,
                                (uint32_t)((bits >> 32) & UINT64_C(65535)));
        } else {
            lo = (uint32_t)(int32_t)words[address];
            rc = write_register(io, KWT1_REG_LOAD_LO, lo);
        }
        if (rc != KWT1_OK) {
            return rc;
        }
        rc = write_register(io, KWT1_REG_LOAD_COMMIT, 1);
        if (rc != KWT1_OK) {
            return rc;
        }
    }
    return KWT1_OK;
}

static int32_t signed_word(uint32_t value)
{
    /* Avoid implementation-defined unsigned-to-signed narrowing for negatives. */
    return value <= INT32_MAX ? (int32_t)value : -1 - (int32_t)(~value);
}

int kwt1_run(const kwt1_io *io, uint32_t m, uint32_t n,
             const int16_t *x, const int16_t *w_pack, const int64_t *bias,
             uint32_t shift, int32_t *y, uint8_t *flags, uint32_t poll_limit)
{
    uint32_t value;
    int rc;
    if (io == NULL || io->read32 == NULL || io->write32 == NULL ||
        x == NULL || w_pack == NULL || bias == NULL || y == NULL ||
        m == 0 || n == 0 || m > UINT16_MAX || n > UINT16_MAX ||
        shift > 47 || poll_limit == 0) {
        return KWT1_ERR_ARGUMENT;
    }
#if SIZE_MAX <= UINT32_MAX
    /* m/n are at most 65535, so X/W/bias byte sizes already fit RV32.
     * The product-sized output buffer needs a separate RV32 bound. */
    if ((uint64_t)m * n > SIZE_MAX / sizeof(*y)) {
        return KWT1_ERR_ARGUMENT;
    }
#endif
    for (uint32_t col = 0; col < n; col++) {
        if (bias[col] < -INT64_C(140737488355328) || bias[col] > INT64_C(140737488355327)) {
            return KWT1_ERR_ARGUMENT;
        }
    }
    rc = read_register(io, KWT1_REG_ID, &value);
    if (rc != KWT1_OK) {
        return rc;
    }
    if (value != KWT1_ID_VALUE) {
        return KWT1_ERR_ID;
    }
    rc = read_register(io, KWT1_REG_GEOMETRY, &value);
    if (rc != KWT1_OK) {
        return rc;
    }
    if (value != ((n << 16) | m)) {
        return KWT1_ERR_GEOMETRY;
    }
    rc = read_register(io, KWT1_REG_DOT_LENGTH, &value);
    if (rc != KWT1_OK) {
        return rc;
    }
    if (value != KWT1_DOT_LENGTH) {
        return KWT1_ERR_GEOMETRY;
    }
    rc = read_status(io, &value);
    if (rc != KWT1_OK) {
        return rc;
    }
    if ((value & KWT1_STATUS_BUSY) != 0) {
        return KWT1_ERR_BUSY;
    }
    if ((value & KWT1_STATUS_ROW_READY) != 0) {
        return KWT1_ERR_PROTOCOL;
    }
    rc = check_error(io);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = write_register(io, KWT1_REG_COMMAND, 1);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = write_register(io, KWT1_REG_SHIFT, shift);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = load_bank(io, 0, m * 64, x, NULL);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = load_bank(io, 1, n * 64, w_pack, NULL);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = load_bank(io, 2, n, NULL, bias);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = wait_status(io, WAIT_LOADED, poll_limit);
    if (rc != KWT1_OK) {
        return rc;
    }
    rc = write_register(io, KWT1_REG_COMMAND, 2);
    if (rc != KWT1_OK) {
        return rc;
    }
    for (uint32_t row = 0; row < m; row++) {
        rc = wait_status(io, WAIT_ROW, poll_limit);
        if (rc != KWT1_OK) {
            return rc;
        }
        rc = read_register(io, KWT1_REG_ROW_INDEX, &value);
        if (rc != KWT1_OK) {
            return rc;
        }
        if (value != row) {
            return KWT1_ERR_PROTOCOL;
        }
        for (uint32_t col = 0; col < n; col++) {
            uint32_t data, row_flags;
            size_t index = (size_t)row * n + col;
            rc = write_register(io, KWT1_REG_ROW_ADDR, col);
            if (rc != KWT1_OK) {
                return rc;
            }
            rc = read_register(io, KWT1_REG_ROW_DATA, &data);
            if (rc != KWT1_OK) {
                return rc;
            }
            rc = read_register(io, KWT1_REG_ROW_FLAGS, &row_flags);
            if (rc != KWT1_OK) {
                return rc;
            }
            if ((row_flags & ~UINT32_C(7)) != 0 || (row_flags & 4) == 0) {
                return KWT1_ERR_PROTOCOL;
            }
            y[index] = signed_word(data);
            if (flags != NULL) {
                flags[index] = (uint8_t)row_flags;
            }
        }
        rc = write_register(io, KWT1_REG_ROW_ACK, row);
        if (rc != KWT1_OK) {
            return rc;
        }
    }
    rc = wait_status(io, WAIT_DONE, poll_limit);
    if (rc != KWT1_OK) {
        return rc;
    }
    return check_error(io);
}
