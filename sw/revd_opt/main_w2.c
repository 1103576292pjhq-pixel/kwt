#include "revd_opt_driver_w2.h"
int main(void)
{
    const volatile uint32_t *config=(const volatile uint32_t *)(uintptr_t)0xa0000100u;
    const volatile revd_opt_task *tasks=(const volatile revd_opt_task *)(uintptr_t)0xa0000120u;
    volatile uint32_t *phase=(volatile uint32_t *)(uintptr_t)0xa0000040u;
    uint32_t m=config[0],n=config[1],count=config[2];
    if(count<1||count>2)return -20;
    for(uint32_t t=0;t<count;t++){
        *phase=t+1;
        int error=revd_opt_run_w2(m,n,&tasks[t]);
        if(error)return error;
        *phase=0x100u+t;
    }
    return 0;
}
