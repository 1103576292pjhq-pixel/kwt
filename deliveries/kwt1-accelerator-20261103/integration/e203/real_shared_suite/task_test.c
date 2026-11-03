// Shared-data test derivative; original task_smoke/task_test.c is preserved.
#include "task_test.h"

#include "shared_task.h"

volatile struct kwt_diagnostics kwt_diag;

static uint32_t fail(uint32_t code)
{
    kwt_diag.error = kwt_read32(KWT_ERROR);
    return code;
}

static uint32_t status_read(void)
{
    uint32_t status = kwt_read32(KWT_STATUS);
    kwt_diag.status = status;
    return status;
}

/* Called only after STATUS reports a complete readable block. Reading the
 * last word is not enough: identity/count ACK releases the result storage. */
static uint32_t drain_block(void)
{
    uint32_t block = kwt_diag.blocks;
    uint32_t group = block % 25u, tile = block / 25u;
    uint32_t row = group*4u, count = group == 24u ? 48u : 64u;
    if (block >= 400u || kwt_read32(KWT_RESULT_TASK) != KWT_TEST_TASK)
        return fail(0x50);
    if (kwt_read32(KWT_RESULT_SEQ) != block+1u ||
        kwt_read32(KWT_RESULT_META) != (row | (tile << 8) | (count << 16)))
        return fail(0x51);
    if (kwt_read32(KWT_RESULT_CURSOR) != 0) return fail(0x52);
    for (uint32_t pos=0; pos<count; ++pos) {
        uint32_t r = row+pos/16u, column = tile*16u+pos%16u;
        uint32_t actual = kwt_read32(KWT_RESULT_DATA);
        kwt_diag.position = r*256u+column;
        kwt_diag.actual = actual;
        shared_write32(SHARED_Y+4u*(r*256u+column),actual);
        ++kwt_diag.outputs;
    }
    if (kwt_read32(KWT_RESULT_CURSOR) != count) return fail(0x55);
    kwt_write32(KWT_ACK_TASK, KWT_TEST_TASK);
    kwt_write32(KWT_ACK_SEQ, block+1u);
    kwt_write32(KWT_ACK_COUNT, count);
    kwt_write32(KWT_ACK, 1);
    kwt_diag.blocks = block+1u;
    return 0;
}

/* One CPU owns this command producer. Poll before COMMAND to avoid bus-error
 * traps. Result servicing cannot change TASK/LAYER/TILE/INDEX/DATA shadows. */
static uint32_t send_command(uint32_t op, uint32_t index, uint32_t data)
{
    kwt_diag.phase = 0x100u | op;
    kwt_write32(KWT_INDEX, index);
    kwt_write32(KWT_DATA, data);
    for (uint32_t polls=0; polls<KWT_WAIT_LIMIT; ++polls) {
        uint32_t status = status_read();
        if (status & 0x90u) return fail(0x41);  /* fault or abort */
        if (status & 0x20u) {
            uint32_t code = drain_block();
            if (code) return code;
        } else if (status & 1u) {
            kwt_write32(KWT_COMMAND, op);
            return 0;
        }
    }
    return fail(0x42);
}

uint32_t kwt_task_test(void)
{
    kwt_diag.phase=0;kwt_diag.blocks=0;kwt_diag.outputs=0;kwt_diag.position=0;
    kwt_diag.expected=0;kwt_diag.actual=0;kwt_diag.status=0;kwt_diag.error=0;
    uint32_t code, status = status_read();
    if (status & 0x90u) return fail(0x41);
    if ((status & 0xb3u) != 1u || kwt_read32(KWT_ERROR)) return fail(0x40);
    if (kwt_suite_sequence>1u && !(status & 8u)) return fail(0x40);
    kwt_write32(KWT_TASK, KWT_TEST_TASK);
    kwt_write32(KWT_LAYER, kwt_suite_layer);
    kwt_write32(KWT_TILE, 0);
    code = send_command(KWT_CMD_BEGIN, 0, 0);
    if (code) return code;
    for (uint32_t i=0; i<6336u; ++i) {
        code = send_command(KWT_CMD_X, i, shared_read32(SHARED_X+4u*i));
        if (code) return code;
    }
    for (uint32_t tile=0; tile<16u; ++tile) {
        kwt_write32(KWT_TILE, tile);
        code = send_command(KWT_CMD_OPEN, 0, 0);
        if (code) return code;
        for (uint32_t i=0; i<1024u; ++i) {
            code = send_command(KWT_CMD_W, i, shared_read32(SHARED_W+4u*((i/16u)*256u+tile*16u+i%16u)));
            if (code) return code;
        }
        for (uint32_t i=0; i<16u; ++i) {
            code = send_command(KWT_CMD_BIAS, i, shared_read32(SHARED_BIAS+4u*(tile*16u+i)));
            if (code) return code;
        }
        code = send_command(KWT_CMD_COMMIT, 0, 0);
        if (code) return code;
        if (tile == 0) {
            code = send_command(KWT_CMD_START, 0, 0); /* First committed tile. */
            if (code) return code;
        }
    }
    kwt_diag.phase = 0x200u;
    uint32_t idle_polls = 0;
    while (kwt_diag.blocks < 400u) {
        status = status_read();
        if (status & 0x90u) return fail(0x41);
        if (status & 0x20u) {
            code = drain_block();
            if (code) return code;
            idle_polls = 0;
        } else if (++idle_polls == KWT_WAIT_LIMIT) return fail(0x56);
    }
    kwt_diag.phase = 0x300u;
    for (uint32_t polls=0; polls<KWT_WAIT_LIMIT; ++polls) {
        status = status_read();
        if (status & 0x90u) return fail(0x41);
        if (status & 8u) {
            if (!(status & 4u) || (status & 0x22u) ||
                kwt_diag.outputs != 25344u || kwt_read32(KWT_ERROR)) return fail(0x57);
            kwt_diag.phase = 0x400u;
            return 1;
        }
    }
    return fail(0x58);
}
