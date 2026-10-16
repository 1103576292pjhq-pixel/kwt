#ifndef KWT_ENCODER_DRIVER_H
#define KWT_ENCODER_DRIVER_H
#include <stdint.h>
#include <stddef.h>
enum { ENC_ID=0,ENC_STATUS=4,ENC_COMMAND=8,ENC_ERROR=12,ENC_ADDR=16,
 ENC_INPUT=20,ENC_WEIGHT=24,ENC_OUTPUT=28,ENC_LAYER=32,ENC_X_COUNT=36,
 ENC_W_COUNT=40,ENC_CYCLES_LO=44,ENC_CYCLES_HI=48,ENC_FLAGS=52,
 ENC_GEOMETRY=56,ENC_H=60,ENC_WORDS=64,ENC_WAIT_DONE=68 };
enum { ENC_OK=0,ENC_ARGUMENT=-1,ENC_IO=-2,ENC_DEVICE=-3,ENC_TIMEOUT=-4,ENC_SEQUENCE=-5 };
typedef struct {
 void *context;
 int (*read32)(void *,uint32_t,uint32_t *);
 int (*write32)(void *,uint32_t,uint32_t);
} encoder_io;
int encoder_begin(const encoder_io *,unsigned,unsigned,unsigned,const uint32_t *);
int encoder_layer(const encoder_io *,unsigned,unsigned,unsigned,unsigned,
                  const uint32_t *,uint32_t *,uint32_t);
/* policy 0: diagnostic full readback+swap; 1: pingpong/final readback only;
 * 2: external full readback/reload. Identical arithmetic in all policies. */
int encoder_layer_mode(const encoder_io *,unsigned,unsigned,unsigned,unsigned,
                       const uint32_t *,uint32_t *,uint32_t,unsigned);
#endif
