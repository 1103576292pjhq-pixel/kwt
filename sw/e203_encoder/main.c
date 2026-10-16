#include "../encoder_driver.h"
#ifndef ENCODER_M
#define ENCODER_M 99
#define ENCODER_D 64
#define ENCODER_H 256
#endif
#ifndef ENCODER_POLICY
#define ENCODER_POLICY 0
#endif
static int read32(void *p,uint32_t r,uint32_t *v) {
 (void)p;__asm__ volatile("fence iorw,iorw":::"memory");
 *v=*(volatile uint32_t *)(0x11010000u+r);return 0;
}
static int write32(void *p,uint32_t r,uint32_t v) {
 (void)p;*(volatile uint32_t *)(0x11010000u+r)=v;
 __asm__ volatile("fence iorw,iorw":::"memory");return 0;
}
// GCC may lower a local aggregate initializer to memcpy even freestanding.
void *memcpy(void *destination,const void *source,size_t count) {
 unsigned char *d=destination;const unsigned char *s=source;size_t i;
 for(i=0;i<count;i++)d[i]=s[i];
 return destination;
}
int main(void) {
 volatile uint32_t *mail=(volatile uint32_t *)0xa0000000u;
 const uint32_t *input=(const uint32_t *)0xa0001000u;
 const uint32_t *weight=(const uint32_t *)0xa0008000u;
 uint32_t *output=(uint32_t *)0xa0040000u;
 encoder_io io={0,read32,write32};unsigned l,wait;int rc;uint32_t start,end;
 // Verify that the original FFN1 MMIO window remains routed on this same SoC.
 if(*(volatile uint32_t *)0x11000000u!=0x4b575431u)return 91;
 if((rc=encoder_begin(&io,ENCODER_M,ENCODER_D,ENCODER_H,input)))return -rc+100;
 for(l=0;l<12;l++) {
  mail[9]=0xffffffffu;mail[8]=l;
  __asm__ volatile("fence rw,rw":::"memory");
  mail[10]=0x4c4f4144u;
  for(wait=0;wait<10000000u&&mail[9]!=l;wait++)__asm__ volatile("nop");
  if(wait==10000000u)return 201;
  __asm__ volatile("rdcycle %0":"=r"(start));
  rc=encoder_layer_mode(&io,ENCODER_M,ENCODER_D,ENCODER_H,l,weight,output,100000000u,ENCODER_POLICY);
  __asm__ volatile("rdcycle %0":"=r"(end));
  if(rc)return -rc+300;
  mail[16+l]=end-start;mail[11]=l+1;
 }
 return 0;
}
