#include "shared_task.h"
#include "fixture.h"
volatile struct shared_diagnostics shared_diag;

uint32_t shared_task_test(void) {
    shared_diag.phase=0x100u;
    for(uint32_t i=0;i<6336u;i++)shared_write32(SHARED_X+4u*i,(uint32_t)fixture_x(i/64u,i%64u));
    for(uint32_t i=0;i<16384u;i++)shared_write32(SHARED_W+4u*i,(uint32_t)fixture_w(i/256u,i%256u));
    for(uint32_t i=0;i<256u;i++)shared_write32(SHARED_BIAS+4u*i,(uint32_t)fixture_bias(i));
    /* 完整结果区预填非法高位模式；漏写不能靠上次内容偶然通过。 */
    for(uint32_t i=0;i<25344u;i++)shared_write32(SHARED_Y+4u*i,0xdeadbeefu);
    shared_write32(GUARD_BEFORE,0x13579bdfu);shared_write32(GUARD_AFTER,0x2468ace0u);
    shared_diag.phase=0x200u;
    uint32_t code=kwt_task_test();
    if(code!=1)return code;
    /* 必须从共享SRAM完整回读，不用刚读到的加速器数据替代写回检查。 */
    shared_diag.phase=0x300u;
    for(uint32_t i=0;i<25344u;i++) {
        uint32_t actual=shared_read32(SHARED_Y+4u*i);
        uint32_t expected=fixture_expected(i/256u,i%256u);
        shared_diag.position=i;shared_diag.expected=expected;shared_diag.actual=actual;
        if(actual!=expected)return 0x70;
        shared_diag.verified=i+1u;
    }
    shared_diag.phase=0x400u;
    if(shared_read32(GUARD_BEFORE)!=0x13579bdfu||shared_read32(GUARD_AFTER)!=0x2468ace0u)return 0x71;
    shared_diag.phase=0x500u;
    return 1;
}
