#ifndef KWT_TASK_TEST_H
#define KWT_TASK_TEST_H
#include <stdint.h>
/* Offsets supplement the passed mmio_smoke header; build checks RTL agreement. */
#include "kwt_mmio.h"
#define KWT_COMMAND       0x18u
#define KWT_RESULT_TASK   0x20u
#define KWT_RESULT_META   0x24u
#define KWT_RESULT_SEQ    0x28u
#define KWT_RESULT_CURSOR 0x2cu
#define KWT_RESULT_DATA   0x30u
#define KWT_ACK           0x40u
#define KWT_CMD_BEGIN  0u
#define KWT_CMD_X      1u
#define KWT_CMD_OPEN   2u
#define KWT_CMD_W      3u
#define KWT_CMD_BIAS   4u
#define KWT_CMD_COMMIT 5u
#define KWT_CMD_START  6u

#define KWT_TEST_TASK 0x51200010u
#define KWT_WAIT_LIMIT 100000u

struct kwt_diagnostics {
    uint32_t phase, blocks, outputs, position, expected, actual, status, error;
};
extern volatile struct kwt_diagnostics kwt_diag;
uint32_t kwt_task_test(void);
#endif
