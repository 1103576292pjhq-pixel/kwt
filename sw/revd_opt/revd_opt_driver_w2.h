#ifndef REVD_OPT_DRIVER_W2_H
#define REVD_OPT_DRIVER_W2_H
#include <stdint.h>
// Shared descriptor: offsets are relative to the 512 KiB shared SRAM window.
typedef struct {
    uint32_t task_id, layer, shift, x_offset, w_offset, b_offset;
    uint32_t y_offset, flags_offset;
} revd_opt_task;
int revd_opt_run_w2(uint32_t m,uint32_t n,const volatile revd_opt_task *task);
#endif
