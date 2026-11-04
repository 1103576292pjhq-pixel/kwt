#include "shared_task.h"
/* 黄金位于独立共享区域，由文件加载器写入，不从被测结果生成。 */
#define SHARED_GOLD (SHARED_BASE+0x40000u)
volatile struct shared_diagnostics shared_diag;

uint32_t shared_task_test(void) {
    shared_diag.phase=0x100u;
    for(uint32_t i=0;i<25344u;i++)shared_write32(SHARED_Y+4u*i,0xdeadbeefu);
    shared_write32(GUARD_BEFORE,0x13579bdfu);
    shared_write32(GUARD_AFTER,0x2468ace0u);
    shared_diag.phase=0x200u;
    uint32_t code=kwt_task_test();
    if(code!=1)return code;
    shared_diag.phase=0x300u;
    for(uint32_t i=0;i<25344u;i++) {
        uint32_t actual=shared_read32(SHARED_Y+4u*i);
        uint32_t expected=shared_read32(SHARED_GOLD+4u*i);
        shared_diag.position=i;shared_diag.actual=actual;shared_diag.expected=expected;
        if(actual!=expected)return 0x70;
        shared_diag.verified=i+1u;
    }
    shared_diag.phase=0x400u;
    if(shared_read32(GUARD_BEFORE)!=0x13579bdfu||shared_read32(GUARD_AFTER)!=0x2468ace0u)return 0x71;
    shared_diag.phase=0x500u;
    return 1;
}
