#include "shared_task.h"
volatile struct shared_diagnostics shared_diag;
volatile struct suite_diagnostics suite_diag;
uint32_t kwt_suite_sequence,kwt_suite_layer;

static uint32_t run_one(void) {
    shared_diag.phase=0x100u;shared_diag.verified=0;
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

uint32_t shared_task_test(void) {
    uint32_t count=shared_read32(SUITE_TOTAL);
    if(count==0 || count>12)return 0x72;
    for(uint32_t sequence=1;sequence<=count;sequence++) {
        uint32_t poll;
        for(poll=0;poll<KWT_WAIT_LIMIT;poll++) {
            uint32_t ready=shared_read32(SUITE_READY);
            if(ready==sequence)break;
            if(ready>sequence)return 0x73;
        }
        if(poll==KWT_WAIT_LIMIT)return 0x74;
        kwt_suite_sequence=sequence;kwt_suite_layer=shared_read32(SUITE_LAYER);
        if(kwt_suite_layer>11)return 0x75;
        uint32_t code=run_one();
        if(code!=1)return code;
        suite_diag.completed=sequence;suite_diag.outputs+=kwt_diag.outputs;
        suite_diag.verified+=shared_diag.verified;
        /* 请求响应完整退休后测试主机才可接管共享口；CPU轮询期间允许背压。 */
        if(sequence<count)shared_write32(SUITE_NEXT,sequence+1u);
    }
    return 1;
}
