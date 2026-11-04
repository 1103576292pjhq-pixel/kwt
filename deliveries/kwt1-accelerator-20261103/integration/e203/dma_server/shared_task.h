#ifndef KWT_SHARED_TASK_H
#define KWT_SHARED_TASK_H
#include "task_test.h"
#define SHARED_BASE  0xa0000000u
#define SHARED_X     (SHARED_BASE+0x00000u)
#define SHARED_W     (SHARED_BASE+0x08000u)
#define SHARED_BIAS  (SHARED_BASE+0x18000u)
#define SHARED_Y     (SHARED_BASE+0x20000u)
#define GUARD_BEFORE (SHARED_Y-4u)
#define GUARD_AFTER  (SHARED_Y+25344u*4u)
uint32_t shared_read32(uint32_t address);
void shared_write32(uint32_t address,uint32_t value);
struct shared_diagnostics {uint32_t phase,verified,position,expected,actual;};
extern volatile struct shared_diagnostics shared_diag;
uint32_t shared_task_test(void);
#endif
