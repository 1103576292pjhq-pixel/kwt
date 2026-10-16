#include "../../sw/encoder_driver.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
typedef struct {unsigned calls,fail,timeout,layer,badid,sticky,words,wcount,xcount,reads,swaps,addr,reload;} fake;
static int read32(void *p,uint32_t r,uint32_t *v) {
 fake *f=p;if(++f->calls==f->fail)return -1;
 *v=0;
 switch(r) {
 case ENC_ID:*v=f->badid?0:0x454e4331;break;
 case ENC_GEOMETRY:*v=(3<<16)|4;break;
 case ENC_H:*v=8;break;
 case ENC_WORDS:*v=160;break;
 case ENC_LAYER:*v=f->layer;break;
 case ENC_W_COUNT:*v=f->wcount;break;
 case ENC_STATUS:case ENC_WAIT_DONE:*v=f->sticky?8:f->timeout?1:2|(f->layer==11?4:0);break;
 case ENC_OUTPUT:*v=0x3f800000+f->addr++;f->reads++;break;
 }
 return 0;
}
static int write32(void *p,uint32_t r,uint32_t v) {
 fake *f=p;if(++f->calls==f->fail)return -1;
 if(r==ENC_ADDR)f->addr=v;
 if(r==ENC_INPUT){if(f->reload)assert(v==0x3f800000+f->xcount);assert(f->addr++==f->xcount++);}
 if(r==ENC_WEIGHT){assert(f->addr++==f->wcount++);assert(v==0);}
 if(r==ENC_COMMAND&&(v==5||v==7)){f->swaps++;f->layer++;f->wcount=0;f->reload=v==7;}
 return 0;
}
int main(void) {
 fake f={0};encoder_io io={&f,read32,write32};uint32_t x[12]={0},w[160]={0},y[12];unsigned i,checks=0;
 assert(encoder_begin(0,3,4,8,x)==ENC_ARGUMENT);checks++;
 assert(encoder_begin(&io,3,4,8,0)==ENC_ARGUMENT);checks++;
 f.badid=1;assert(encoder_begin(&io,3,4,8,x)==ENC_DEVICE);checks++;
 memset(&f,0,sizeof f);f.fail=1;assert(encoder_begin(&io,3,4,8,x)==ENC_IO);checks++;
 memset(&f,0,sizeof f);assert(encoder_begin(&io,3,4,8,x)==0);assert(f.xcount==12);checks++;
 assert(encoder_layer(&io,3,4,8,1,w,y,10)==ENC_SEQUENCE);checks++;
 assert(encoder_layer(&io,3,4,8,12,w,y,10)==ENC_ARGUMENT);checks++;
 assert(encoder_layer(&io,3,4,8,0,w,y,0)==ENC_ARGUMENT);checks++;
 assert(encoder_layer(&io,3,4,8,0,w,y,10)==0);assert(f.reads==12&&f.swaps==1);checks++;
 for(i=0;i<12;i++)assert(y[i]==0x3f800000+i);
 memset(&f,0,sizeof f);f.timeout=1;assert(encoder_layer(&io,3,4,8,0,w,y,3)==ENC_TIMEOUT);assert(!f.reads&&!f.swaps);checks++;
 memset(&f,0,sizeof f);f.sticky=1;assert(encoder_layer(&io,3,4,8,0,w,y,3)==ENC_DEVICE);checks++;
 memset(&f,0,sizeof f);f.fail=20;assert(encoder_layer(&io,3,4,8,0,w,y,3)==ENC_IO);checks++;
 memset(&f,0,sizeof f);f.layer=11;assert(encoder_layer(&io,3,4,8,11,w,y,3)==0);assert(!f.swaps&&f.reads==12);checks++;
 memset(&f,0,sizeof f);assert(encoder_layer_mode(&io,3,4,8,0,w,y,3,1)==0);assert(f.swaps==1&&!f.reads&&!f.xcount);
 memset(&f,0,sizeof f);assert(encoder_layer_mode(&io,3,4,8,0,w,y,3,2)==0);assert(f.swaps==1&&f.reads==12&&f.xcount==12&&f.reload);
 memset(&f,0,sizeof f);assert(encoder_layer_mode(&io,3,4,8,0,w,y,3,3)==ENC_ARGUMENT);assert(!f.calls);
 printf("ENCODER_DRIVER_PASS checks=%u\n",checks);return 0;
}
