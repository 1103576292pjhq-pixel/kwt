#include <stdio.h>
#include <stdlib.h>
#include "../shared_task.h"

static FILE *requests,*responses;
static unsigned int transactions;
static uint32_t access_bus(unsigned int rd,uint32_t address,uint32_t value) {
    unsigned int got,error;
    if(fprintf(requests,"%u %x %x\n",rd,address,value)<0||fflush(requests))exit(5);
    if(fscanf(responses,"%x %u",&got,&error)!=2)exit(6);
    transactions++;
    if(error){fprintf(stderr,"ICB_ERROR address=%x read=%u\n",address,rd);exit(7);}
    return got;
}
unsigned int kwt_read32(unsigned int offset){return access_bus(1,KWT_BASE+offset,0);}
void kwt_write32(unsigned int offset,unsigned int value){(void)access_bus(0,KWT_BASE+offset,value);}
uint32_t shared_read32(uint32_t address){return access_bus(1,address,0);}
void shared_write32(uint32_t address,uint32_t value){(void)access_bus(0,address,value);}
int main(int argc,char **argv) {
    if(argc!=3)return 4;
    requests=fopen(argv[1],"w");responses=fopen(argv[2],"r");
    if(!requests||!responses)return 4;
    uint32_t code=shared_task_test();
    printf("SHARED_TASK code=%x blocks=%u outputs=%u verified=%u phase=%x position=%u expected=%x actual=%x transactions=%u\n",
           code,kwt_diag.blocks,kwt_diag.outputs,shared_diag.verified,shared_diag.phase,
           shared_diag.position,shared_diag.expected,shared_diag.actual,transactions);
    printf("SUITE_COUNTS completed=%u outputs=%u verified=%u\n",suite_diag.completed,suite_diag.outputs,suite_diag.verified);
    fprintf(requests,"2 0 0\n");fflush(requests);fclose(requests);fclose(responses);
    return code==1?0:1;
}
