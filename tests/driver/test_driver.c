#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ffn1_driver.h"

/* An ordered bus transcript is the oracle. It supplies known RTL responses,
 * checks each requested access, and never computes a dot/matrix answer. */
typedef struct access {
    int write;
    uint32_t offset;
    uint32_t value;
    int fail;
} access;

typedef struct transcript {
    access access[2048];
    size_t count;
    size_t cursor;
    int mismatch;
    int32_t *output;
    uint8_t *flags;
} transcript;

static unsigned tests;
static unsigned failures;
static int16_t input[2 * 64];
static int16_t weights[3 * 64];
static const int64_t biases[3] = {
    -INT64_C(140737488355328), -INT64_C(1), INT64_C(140737488355327)
};
static const int32_t expected[6] = {
    INT32_MIN, -1, 0, 1, INT32_MAX, -123456789
};
static const uint8_t expected_flags[6] = {4, 5, 6, 7, 4, 4};

static void require(int condition, const char *message, unsigned line)
{
    if (!condition) {
        fprintf(stderr, "FAIL line %u: %s\n", line, message);
        failures++;
    }
}

#define REQUIRE(condition) require((condition), #condition, __LINE__)

static void append(transcript *t, int write, uint32_t offset, uint32_t value)
{
    if (t->count >= sizeof(t->access) / sizeof(t->access[0])) {
        fputs("transcript overflow\n", stderr);
        exit(2);
    }
    t->access[t->count++] = (access){write, offset, value, 0};
}

static int transaction(transcript *t, int write, uint32_t offset, uint32_t *value)
{
    access a;
    if (t->cursor >= t->count) {
        t->mismatch = 1;
        fprintf(stderr, "unexpected %c offset=0x%02" PRIx32 "\n", write ? 'W' : 'R', offset);
        return -1;
    }
    a = t->access[t->cursor++];
    if (a.write != write || a.offset != offset || (write && a.value != *value)) {
        t->mismatch = 1;
        fprintf(stderr, "bus mismatch #%zu: %c 0x%02" PRIx32 " value=%08" PRIx32
                ", expected %c 0x%02" PRIx32 " value=%08" PRIx32 "\n",
                t->cursor - 1, write ? 'W' : 'R', offset, *value,
                a.write ? 'W' : 'R', a.offset, a.value);
        return -1;
    }
    if (a.fail) {
        return 23;
    }
    if (write && offset == 0x38 && t->output != NULL) {
        size_t row = *value;
        for (size_t col = 0; col < 3; col++) {
            size_t index = row * 3 + col;
            /* The CPU must store every output/flag before releasing the row. */
            if (t->output[index] != expected[index] ||
                (t->flags != NULL && t->flags[index] != expected_flags[index])) {
                t->mismatch = 1;
                fputs("ACK before output became visible\n", stderr);
                return -1;
            }
        }
    }
    if (!write) {
        *value = a.value;
    }
    return 0;
}

static int read32(void *context, uint32_t offset, uint32_t *value)
{
    *value = 0;
    return transaction(context, 0, offset, value);
}

static int write32(void *context, uint32_t offset, uint32_t value)
{
    return transaction(context, 1, offset, &value);
}

static kwt1_io make_io(transcript *t)
{
    kwt1_io io = {t, read32, write32};
    return io;
}

static void initial(transcript *t, uint32_t m, uint32_t n)
{
    append(t, 0, 0x00, UINT32_C(0x4b575431));
    append(t, 0, 0x3c, (n << 16) | m);
    append(t, 0, 0x40, 64);
    append(t, 0, 0x04, 0);
    append(t, 0, 0x0c, 0);
}

static void prepare_loading(transcript *t, uint32_t shift)
{
    initial(t, 2, 3);
    append(t, 1, 0x08, 1);
    append(t, 1, 0x10, shift);
    for (uint32_t kind = 0; kind < 3; kind++) {
        append(t, 1, 0x14, kind);
        for (uint32_t i = 0; i < (kind == 0 ? 128u : kind == 1 ? 192u : 3u); i++) {
            append(t, 1, 0x18, i);
            if (kind < 2) {
                int16_t v = kind == 0 ? input[i] : weights[i];
                append(t, 1, 0x1c, (uint32_t)(int32_t)v);
            } else {
                /* Deliberately explicit expectations for the three signed48
                 * extrema; independent of the driver's splitting code. */
                static const uint32_t lo[3] = {0, UINT32_MAX, UINT32_MAX};
                static const uint32_t hi[3] = {0x8000, 0xffff, 0x7fff};
                append(t, 1, 0x1c, lo[i]);
                append(t, 1, 0x20, hi[i]);
            }
            append(t, 1, 0x24, 1);
        }
    }
}

static void prepare_success(transcript *t)
{
    memset(t, 0, sizeof(*t));
    prepare_loading(t, 47);
    append(t, 0, 0x04, 0);  /* loaded wait */
    append(t, 0, 0x04, 2);
    append(t, 1, 0x08, 2);
    for (uint32_t row = 0; row < 2; row++) {
        append(t, 0, 0x04, 1);
        append(t, 0, 0x04, 5);
        append(t, 0, 0x28, row);
        for (uint32_t col = 0; col < 3; col++) {
            append(t, 1, 0x2c, col);
            append(t, 0, 0x30, (uint32_t)expected[row * 3 + col]);
            append(t, 0, 0x34, expected_flags[row * 3 + col]);
        }
        append(t, 1, 0x38, row);
    }
    append(t, 0, 0x04, 0);
    append(t, 0, 0x04, 8);
    append(t, 0, 0x0c, 0);
}

static int run(transcript *t, uint8_t *flags)
{
    int32_t y[6] = {99, 99, 99, 99, 99, 99};
    kwt1_io io = make_io(t);
    t->output = y;
    t->flags = flags;
    int rc = kwt1_run(&io, 2, 3, input, weights, biases, 47, y, flags, 3);
    if (rc == KWT1_OK) {
        REQUIRE(memcmp(y, expected, sizeof(y)) == 0);
    }
    return rc;
}

static void checked_result(transcript *t, int actual, int expected_result)
{
    REQUIRE(actual == expected_result);
    REQUIRE(t->mismatch == 0);
    REQUIRE(t->cursor == t->count);
    tests++;
}

static size_t find_access(transcript *t, uint32_t offset, size_t from)
{
    for (size_t i = from; i < t->count; i++) {
        if (t->access[i].offset == offset) {
            return i;
        }
    }
    fputs("test fixture access not found\n", stderr);
    exit(2);
}

static void invalid_arguments(void)
{
    transcript t = {0};
    kwt1_io io = make_io(&t), broken = io;
    int32_t y[6];
    int64_t invalid_bias[3] = {biases[0] - 1, 0, 0};
#define INVALID(call) checked_result(&t, (call), KWT1_ERR_ARGUMENT)
    INVALID(kwt1_run(NULL, 2, 3, input, weights, biases, 0, y, NULL, 1));
    broken.read32 = NULL;
    INVALID(kwt1_run(&broken, 2, 3, input, weights, biases, 0, y, NULL, 1));
    broken = io;
    broken.write32 = NULL;
    INVALID(kwt1_run(&broken, 2, 3, input, weights, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 0, 3, input, weights, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 0, input, weights, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 65536, 3, input, weights, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 65536, input, weights, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 3, NULL, weights, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 3, input, NULL, biases, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 3, input, weights, NULL, 0, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 3, input, weights, biases, 0, NULL, NULL, 1));
    INVALID(kwt1_run(&io, 2, 3, input, weights, biases, 48, y, NULL, 1));
    INVALID(kwt1_run(&io, 2, 3, input, weights, biases, 0, y, NULL, 0));
    INVALID(kwt1_run(&io, 2, 3, input, weights, invalid_bias, 0, y, NULL, 1));
    invalid_bias[0] = biases[0];
    invalid_bias[2] = biases[2] + 1;
    INVALID(kwt1_run(&io, 2, 3, input, weights, invalid_bias, 0, y, NULL, 1));
#undef INVALID
}

static void preflight_failures(void)
{
    transcript t;
    const struct { size_t at; uint32_t value; int code; } bad[] = {
        {0, 0, KWT1_ERR_ID},
        {1, 0x00030001, KWT1_ERR_GEOMETRY},
        {1, 0x00040002, KWT1_ERR_GEOMETRY},
        {2, 63, KWT1_ERR_GEOMETRY},
        {3, 1, KWT1_ERR_BUSY},
        {3, 4, KWT1_ERR_PROTOCOL},
        {3, 0x20, KWT1_ERR_PROTOCOL},
        {3, 16, KWT1_ERR_CORE},
        {4, 1, KWT1_ERR_CORE},
        {4, 0x10, KWT1_ERR_CORE}
    };
    for (size_t i = 0; i < sizeof(bad) / sizeof(bad[0]); i++) {
        memset(&t, 0, sizeof(t));
        initial(&t, 2, 3);
        t.access[bad[i].at].value = bad[i].value;
        t.count = bad[i].at + 1;
        checked_result(&t, run(&t, NULL), bad[i].code);
    }
}

static void truncate_with_value(uint32_t offset, size_t ordinal, uint32_t value, int code)
{
    transcript t;
    size_t at = 0;
    prepare_success(&t);
    for (size_t i = 0; i <= ordinal; i++) {
        at = find_access(&t, offset, i == 0 ? 0 : at + 1);
    }
    t.access[at].value = value;
    t.count = at + 1;
    checked_result(&t, run(&t, NULL), code);
}

static void protocol_failures(void)
{
    truncate_with_value(0x28, 0, 1, KWT1_ERR_PROTOCOL);
    truncate_with_value(0x28, 1, 0, KWT1_ERR_PROTOCOL);
    truncate_with_value(0x34, 0, 0, KWT1_ERR_PROTOCOL);
    truncate_with_value(0x34, 1, 8, KWT1_ERR_PROTOCOL);
    truncate_with_value(0x04, 1, 1, KWT1_ERR_PROTOCOL); /* busy before START */
    truncate_with_value(0x04, 1, 8, KWT1_ERR_PROTOCOL); /* old DONE not cleared */
    truncate_with_value(0x04, 1, 16, KWT1_ERR_CORE);
    truncate_with_value(0x04, 3, 0, KWT1_ERR_PROTOCOL); /* idle while expecting row */
    truncate_with_value(0x04, 3, 8, KWT1_ERR_PROTOCOL); /* premature DONE */
    truncate_with_value(0x04, 4, 4, KWT1_ERR_PROTOCOL); /* row without BUSY */
    truncate_with_value(0x04, 3, 17, KWT1_ERR_CORE);
    truncate_with_value(0x04, 7, 4, KWT1_ERR_PROTOCOL); /* extra final row */
    truncate_with_value(0x04, 8, 9, KWT1_ERR_PROTOCOL); /* DONE + BUSY */
    truncate_with_value(0x0c, 1, 2, KWT1_ERR_CORE); /* sticky final error */
}

static void timeouts(void)
{
    transcript t;
    size_t at;
    prepare_success(&t);
    at = find_access(&t, 0x04, 4) ; /* first loaded wait, after preflight STATUS */
    t.count = at;
    append(&t, 0, 0x04, 0);
    append(&t, 0, 0x04, 0);
    append(&t, 0, 0x04, 0);
    checked_result(&t, run(&t, NULL), KWT1_ERR_TIMEOUT);

    prepare_success(&t);
    at = find_access(&t, 0x08, find_access(&t, 0x08, 0) + 1) + 1;
    t.count = at;
    append(&t, 0, 0x04, 1);
    append(&t, 0, 0x04, 1);
    append(&t, 0, 0x04, 1);
    checked_result(&t, run(&t, NULL), KWT1_ERR_TIMEOUT);

    prepare_success(&t);
    at = find_access(&t, 0x38, find_access(&t, 0x38, 0) + 1) + 1;
    t.count = at;
    append(&t, 0, 0x04, 1);
    append(&t, 0, 0x04, 1);
    append(&t, 0, 0x04, 1);
    checked_result(&t, run(&t, NULL), KWT1_ERR_TIMEOUT);
}

static void all_access_failures(void)
{
    transcript t, original;
    prepare_success(&original);
    for (size_t i = 0; i < original.count; i++) {
        t = original;
        t.access[i].fail = 1;
        t.count = i + 1;
        checked_result(&t, run(&t, NULL), KWT1_ERR_IO);
    }
}

static void one_element_and_repeated_jobs(void)
{
    transcript t = {0};
    kwt1_io io = make_io(&t);
    const int16_t x[64] = {0};
    const int16_t w[64] = {0};
    const int64_t bias = 0;
    int32_t y = 99;
    uint8_t flag = 99;
    for (unsigned job = 0; job < 2; job++) {
        /* Job two starts with a previous DONE, which load_begin clears. */
        initial(&t, 1, 1);
        t.access[t.count - 2].value = job == 0 ? 0 : 8;
        append(&t, 1, 0x08, 1);
        append(&t, 1, 0x10, 0);
        for (uint32_t bank = 0; bank < 3; bank++) {
            append(&t, 1, 0x14, bank);
            for (uint32_t address = 0; address < (bank == 2 ? 1u : 64u); address++) {
                append(&t, 1, 0x18, address);
                append(&t, 1, 0x1c, 0);
                if (bank == 2) {
                    append(&t, 1, 0x20, 0);
                }
                append(&t, 1, 0x24, 1);
            }
        }
        append(&t, 0, 0x04, 2);
        append(&t, 1, 0x08, 2);
        append(&t, 0, 0x04, 5);
        append(&t, 0, 0x28, 0);
        append(&t, 1, 0x2c, 0);
        append(&t, 0, 0x30, UINT32_C(0xffffffd6)); /* -42: mock response, not computed */
        append(&t, 0, 0x34, 7);
        append(&t, 1, 0x38, 0);
        append(&t, 0, 0x04, 8);
        append(&t, 0, 0x0c, 0);
    }
    for (unsigned job = 0; job < 2; job++) {
        REQUIRE(kwt1_run(&io, 1, 1, x, w, &bias, 0, &y, &flag, 1) == KWT1_OK);
        REQUIRE(y == -42);
        REQUIRE(flag == 7);
        tests++;
    }
    REQUIRE(t.cursor == t.count);
    REQUIRE(t.mismatch == 0);
}

int main(void)
{
    transcript t;
    uint8_t flags[6] = {0};
    static const int16_t signed_values[] = {INT16_MIN, -1, 0, 1, INT16_MAX, -12345};
    for (size_t i = 0; i < 128; i++) {
        input[i] = signed_values[i % 6];
    }
    for (size_t i = 0; i < 192; i++) {
        weights[i] = signed_values[(i + 1) % 6];
    }
    prepare_success(&t);
    checked_result(&t, run(&t, flags), KWT1_OK);
    REQUIRE(memcmp(flags, expected_flags, sizeof(flags)) == 0);
    prepare_success(&t);
    checked_result(&t, run(&t, NULL), KWT1_OK);
    invalid_arguments();
    preflight_failures();
    protocol_failures();
    timeouts();
    all_access_failures();
    one_element_and_repeated_jobs();
    printf("DRIVER_TESTS=%u FAILURES=%u\n", tests, failures);
    return failures ? 1 : 0;
}
