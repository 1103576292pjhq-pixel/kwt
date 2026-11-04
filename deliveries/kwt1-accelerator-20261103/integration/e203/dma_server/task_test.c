#include "shared_task.h"

/* DMA CSR offsets. Full task and numeric format are fixed by this accelerator. */
#define DMA_ID       0x00u
#define DMA_STATUS   0x04u
#define DMA_CONTROL  0x08u
#define DMA_X_BASE   0x10u
#define DMA_W_BASE   0x14u
#define DMA_B_BASE   0x18u
#define DMA_Y_BASE   0x1cu
#define DMA_TASK     0x20u
#define DMA_LAYER    0x24u
#define DMA_OUTPUTS  0x28u
#define DMA_ERROR    0x30u
#define DMA_BLOCKS   0x34u

volatile struct kwt_diagnostics kwt_diag;

uint32_t kwt_task_test(void)
{
    if (kwt_read32(DMA_ID) != 0x4b444d31u) return 0x80;
    if (kwt_read32(DMA_STATUS) & 1u) return 0x81;
    kwt_write32(DMA_X_BASE, SHARED_X);
    kwt_write32(DMA_W_BASE, SHARED_W);
    kwt_write32(DMA_B_BASE, SHARED_BIAS);
    kwt_write32(DMA_Y_BASE, SHARED_Y);
    kwt_write32(DMA_TASK, KWT_TEST_TASK);
    kwt_write32(DMA_LAYER, 2u);
    kwt_write32(DMA_CONTROL, 1u);
    for (uint32_t poll = 0; poll < 1000000u; ++poll) {
        uint32_t status = kwt_read32(DMA_STATUS);
        if (!(status & 1u)) {
            kwt_diag.status = status;
            kwt_diag.error = kwt_read32(DMA_ERROR);
            kwt_diag.outputs = kwt_read32(DMA_OUTPUTS);
            kwt_diag.blocks = kwt_read32(DMA_BLOCKS);
            if (status != 2u || kwt_diag.error ||
                kwt_diag.outputs != 25344u || kwt_diag.blocks != 400u) return 0x82;
            return 1u;
        }
    }
    kwt_write32(DMA_CONTROL, 2u);
    /* Abort completion owns the in-flight memory drain before buffers may be reused. */
    for (uint32_t poll = 0; poll < 1000000u; ++poll) {
        if (!(kwt_read32(DMA_STATUS) & 1u)) return 0x83;
    }
    return 0x84;
}
