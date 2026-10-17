#include "revd_opt_driver.h"
#define SHARED ((uintptr_t)0xa0000000u)
#define MMIO ((uintptr_t)0x11000000u)
static uint32_t seen[(99u*256u+31u)/32u];
static uint32_t result_count,expected_count,active_task,current_meta;
static volatile int32_t *destination;
static volatile uint8_t *flag_destination;
static uint32_t rd(uint32_t offset){return *(volatile uint32_t *)(MMIO+offset);}
static void wr(uint32_t offset,uint32_t value){*(volatile uint32_t *)(MMIO+offset)=value;}
static int drain(uint32_t status)
{
    if(status&8u)return -11;
    if(status&2u){
        uint32_t index=rd(0x1c),value=rd(0x20),flags=rd(0x24),task_id=rd(0x28);
        if(index>=expected_count||task_id!=active_task)return -12;
        if(seen[index/32u]&(1u<<(index%32u)))return -13;
        if((flags&~7u)||((flags&4u)!=((index+1u==expected_count)?4u:0u)))return -14;
        seen[index/32u]|=1u<<(index%32u);
        destination[index]=(int32_t)value;
        flag_destination[index]=(uint8_t)flags;
        __asm__ volatile("fence iorw,iorw" ::: "memory");
        wr(0x2c,1);
        result_count++;
    }
    return 0;
}
static int emit(uint32_t op,uint32_t layer,uint32_t shift,uint32_t tile,uint32_t index,int64_t value)
{
    uint32_t status;
    for(uint32_t polls=0;;polls++){
        if(polls==2000000u)return -15;
        status=rd(0);
        int error=drain(status);if(error)return error;
        if(status&1u)break;
    }
    uint32_t meta=op|(layer<<4)|(shift<<8);
    if(meta!=current_meta){wr(4,meta);current_meta=meta;}
    wr(12,(tile<<16)|index);
    wr(16,(uint32_t)value);wr(20,(uint32_t)((uint64_t)value>>32));
    __asm__ volatile("fence iorw,iorw" ::: "memory");
    wr(24,1);
    return 0;
}
#define EMIT(op,tile,index,value) do {int error=emit(op,layer,shift,tile,index,value);if(error)return error;}while(0)
int revd_opt_run(uint32_t m,uint32_t n,const volatile revd_opt_task *task)
{
    if(m<1||m>99||n<16||n>256||n%16)return -1;
    uint32_t layer=task->layer,shift=task->shift;
    if(layer<1||layer>12||shift>47)return -2;
    const volatile int16_t *x=(const volatile int16_t *)(SHARED+task->x_offset);
    const volatile int16_t *w=(const volatile int16_t *)(SHARED+task->w_offset);
    const volatile int64_t *b=(const volatile int64_t *)(SHARED+task->b_offset);
    destination=(volatile int32_t *)(SHARED+task->y_offset);
    flag_destination=(volatile uint8_t *)(SHARED+task->flags_offset);
    active_task=task->task_id;expected_count=m*n;result_count=0;current_meta=0xffffffffu;
    for(uint32_t i=0;i<(expected_count+31u)/32u;i++)seen[i]=0;
    wr(8,active_task);EMIT(0,0,0,0);
    for(uint32_t i=0;i<m*64u;i++)EMIT(1,0,i,x[i]);
    for(uint32_t tile=0;tile<n/16u;tile++){
        EMIT(2,tile,0,0);
        for(uint32_t k=0;k<64u;k++)for(uint32_t col=0;col<16u;col++){
            uint32_t index=k*16u+col;
            EMIT(3,tile,index,w[(tile*16u+col)*64u+k]);
        }
        for(uint32_t col=0;col<16u;col++)EMIT(4,tile,col,b[tile*16u+col]);
        EMIT(5,tile,0,0);
    }
    EMIT(6,0,0,0);
    for(uint32_t polls=0;;polls++){
        if(polls==4000000u)return -16;
        uint32_t status=rd(0);int error=drain(status);if(error)return error;
        if(status&4u){if(result_count!=expected_count)return -17;break;}
    }
    __asm__ volatile("fence iorw,iorw" ::: "memory");
    return 0;
}
