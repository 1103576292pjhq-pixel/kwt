#include "encoder_driver.h"
static int valid(const encoder_io *io) {return io&&io->read32&&io->write32;}
static int rd(const encoder_io *io,uint32_t r,uint32_t *v) {return io->read32(io->context,r,v)?ENC_IO:ENC_OK;}
static int wr(const encoder_io *io,uint32_t r,uint32_t v) {return io->write32(io->context,r,v)?ENC_IO:ENC_OK;}
static int check(const encoder_io *io,unsigned m,unsigned d,unsigned h) {
 uint32_t v;int rc;
 if(!valid(io)||!m||m>99||(d!=4&&d!=64)||!h||h>256)return ENC_ARGUMENT;
 if((rc=rd(io,ENC_ID,&v)))return rc;
 if(v!=UINT32_C(0x454e4331))return ENC_DEVICE;
 if((rc=rd(io,ENC_GEOMETRY,&v)))return rc;
 if(v!=((m<<16)|d))return ENC_DEVICE;
 if((rc=rd(io,ENC_H,&v)))return rc;
 if(v!=h)return ENC_DEVICE;
 if((rc=rd(io,ENC_WORDS,&v)))return rc;
 return v==4*d*d+2*d*h+h+6*d?ENC_OK:ENC_DEVICE;
}
int encoder_begin(const encoder_io *io,unsigned m,unsigned d,unsigned h,const uint32_t *input) {
 int rc;unsigned i;
 if(!input)return ENC_ARGUMENT;
 if((rc=check(io,m,d,h)))return rc;
 if((rc=wr(io,ENC_COMMAND,0)))return rc;
 if((rc=wr(io,ENC_ERROR,7)))return rc;
 if((rc=wr(io,ENC_ADDR,0)))return rc;
 for(i=0;i<m*d;i++)if((rc=wr(io,ENC_INPUT,input[i])))return rc;
 return ENC_OK;
}
int encoder_layer(const encoder_io *io,unsigned m,unsigned d,unsigned h,unsigned layer,
 const uint32_t *weight,uint32_t *output,uint32_t poll_limit) {
 return encoder_layer_mode(io,m,d,h,layer,weight,output,poll_limit,0);
}
int encoder_layer_mode(const encoder_io *io,unsigned m,unsigned d,unsigned h,unsigned layer,
 const uint32_t *weight,uint32_t *output,uint32_t poll_limit,unsigned policy) {
 uint32_t v,i,words;int rc;
 if(!weight||!output||layer>=12||!poll_limit||policy>2)return ENC_ARGUMENT;
 if((rc=check(io,m,d,h)))return rc;
 if((rc=rd(io,ENC_LAYER,&v)))return rc;
 if(v!=layer)return ENC_SEQUENCE;
 words=4*d*d+2*d*h+h+6*d;
 if((rc=wr(io,ENC_ADDR,0)))return rc;
 for(i=0;i<words;i++)if((rc=wr(io,ENC_WEIGHT,weight[i])))return rc;
 if((rc=rd(io,ENC_W_COUNT,&v)))return rc;
 if(v!=words)return ENC_SEQUENCE;
 if((rc=wr(io,ENC_COMMAND,3)))return rc;
 // Blocking completion register stalls this real CPU transaction in hardware,
 // with a bounded bridge watchdog; no host substitutes accelerator computation.
 if((rc=rd(io,ENC_WAIT_DONE,&v)))return rc;
 for(i=0;i<poll_limit;i++) {
  if((rc=rd(io,ENC_STATUS,&v)))return rc;
  if(v&8)return ENC_DEVICE;
  if(v&2)break;
  if(!(v&1))return ENC_DEVICE;
 }
 if(i==poll_limit)return ENC_TIMEOUT;
 if(layer==11 && !(v&4))return ENC_SEQUENCE;
 if(layer==11||policy!=1) {
  if((rc=wr(io,ENC_ADDR,0)))return rc;
  for(i=0;i<m*d;i++)if((rc=rd(io,ENC_OUTPUT,&output[i])))return rc;
 }
 if(layer<11) {
  if((rc=wr(io,ENC_COMMAND,policy==2?7:5)))return rc;
  if(policy==2) {
   if((rc=wr(io,ENC_ADDR,0)))return rc;
   for(i=0;i<m*d;i++)if((rc=wr(io,ENC_INPUT,output[i])))return rc;
  }
 }
 return ENC_OK;
}
