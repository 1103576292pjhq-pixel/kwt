#include "shared_task.h"

uint32_t shared_read32(uint32_t address) {
    uint32_t value=*(volatile uint32_t *)(uintptr_t)address;
    __asm__ volatile("fence iorw,iorw":::"memory");return value;
}
void shared_write32(uint32_t address,uint32_t value) {
    *(volatile uint32_t *)(uintptr_t)address=value;
    __asm__ volatile("fence iorw,iorw":::"memory");
}
unsigned int kwt_read32(unsigned int offset){return shared_read32(KWT_BASE+offset);}
void kwt_write32(unsigned int offset,unsigned int value){shared_write32(KWT_BASE+offset,value);}
int main(void){return (int)shared_task_test();}
