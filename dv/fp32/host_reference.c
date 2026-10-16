/* Independent binary32 oracle: host C arithmetic, explicit fmaf and fenv.
 * This file is never linked into the RTL simulator. */
#pragma STDC FENV_ACCESS ON
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static float from_bits(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }
static uint32_t bits(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static unsigned flags(void) {
    int f = fetestexcept(FE_ALL_EXCEPT);
    return ((f & FE_INVALID) ? 16U : 0U) |
           ((f & FE_DIVBYZERO) ? 8U : 0U) |
           ((f & FE_OVERFLOW) ? 4U : 0U) |
           ((f & FE_UNDERFLOW) ? 2U : 0U) |
           ((f & FE_INEXACT) ? 1U : 0U);
}
static uint32_t reference(unsigned op, uint32_t au, uint32_t bu, uint32_t cu,
                          unsigned *fl) {
    volatile float a=from_bits(au), b=from_bits(bu), c=from_bits(cu), result=0;
    feclearexcept(FE_ALL_EXCEPT);
    switch(op) {
    case 0: result=a+b; break;
    case 1: result=a-b; break;
    case 2: result=a*b; break;
    case 3: result=fmaf(a,b,c); break;
    case 4: result=a/b; break;
    case 5: result=sqrtf(a); break;
    case 6: {
        /* Avoid undefined out-of-range C casts. RISC-V HardFloat saturates
         * NaN/+overflow to INT_MAX and -overflow to INT_MIN. */
        double d=(double)a;
        double rounded=nearbyint(d);
        if (isnan(d) || rounded>INT32_MAX) { *fl=16; return INT32_MAX; }
        if (rounded<INT32_MIN) { *fl=16; return UINT32_C(0x80000000); }
        *fl=(rounded==d) ? 0U : 1U;
        return (uint32_t)(int32_t)rounded;
    }
    case 7: { int32_t i; memcpy(&i,&au,4); result=(float)i; break; }
    default: *fl=0; return UINT32_C(0x7fc00000);
    }
    *fl=flags();
    /* RISC-V mandates invalid for inf*zero even if FMA's addend is qNaN.
     * glibc fmaf is allowed to suppress that flag in this IEEE corner.
     * https://docs.riscv.org/reference/isa/unpriv/f-st-ext.html */
    if(op==3 && (((au&0x7fffffff)==0x7f800000 && (bu&0x7fffffff)==0) ||
                 ((bu&0x7fffffff)==0x7f800000 && (au&0x7fffffff)==0))) *fl|=16;
    uint32_t u=bits(result);
    if ((u & UINT32_C(0x7fffffff))>UINT32_C(0x7f800000)) u=UINT32_C(0x7fc00000);
    return u;
}
static uint32_t state=UINT32_C(0x6385f29b);
static uint32_t random_u32(void) { state^=state<<13; state^=state>>17; state^=state<<5; return state; }
static void emit(FILE *f, unsigned op, uint32_t a,uint32_t b,uint32_t c) {
    unsigned fl;
    uint32_t y=reference(op,a,b,c,&fl);
    fprintf(f,"%x %08" PRIx32 " %08" PRIx32 " %08" PRIx32 " %08" PRIx32 " %02x %x\n",
            op,a,b,c,y,fl,op>7);
}
int main(int argc,char **argv) {
    if (argc!=3 || sizeof(float)!=4 || FLT_RADIX!=2 || FLT_MANT_DIG!=24) return 2;
    unsigned count=(unsigned)strtoul(argv[2],NULL,10);
    if (fesetround(FE_TONEAREST)) return 3;
    FILE *out=fopen(argv[1],"w"); if(!out) return 4;
    /* Cartesian corners include signed zeros, both subnormal boundaries,
     * cancellation, ties, infinities, quiet/signaling NaNs, integer edges. */
    const uint32_t corner[]={0,0x80000000,1,0x80000001,0x007fffff,0x807fffff,
        0x00800000,0x80800000,0x3f000000,0xbf000000,0x3fc00000,0xbfc00000,
        0x3f800000,0xbf800000,0x3f800001,0x3f7fffff,0x40000000,0xc0000000,
        0x4b800001,0x4effffff,0x4f000000,0xcf000000,0xcf000001,
        0x7f7fffff,0xff7fffff,0x7f800000,0xff800000,0x7fc12345,0xffc12345,
        0x7f812345,0xff812345};
    const unsigned n=(unsigned)(sizeof(corner)/sizeof(corner[0]));
    unsigned total=0;
    for(unsigned op=0;op<8;op++) {
        for(unsigned i=0;i<n;i++) {
            unsigned limit=(op==5 || op==6 || op==7)?1:n;
            for(unsigned j=0;j<limit;j++) {
                emit(out,op,corner[i],corner[j],corner[(i*7+j*3)%n]); total++;
            }
        }
        for(unsigned j=0;j<count;j++) {
            uint32_t a=random_u32(),b=random_u32(),c=random_u32();
            /* Random finite raw words; special values are covered above. */
            if((a&0x7f800000)==0x7f800000) a^=0x00800000;
            if((b&0x7f800000)==0x7f800000) b^=0x00800000;
            if((c&0x7f800000)==0x7f800000) c^=0x00800000;
            emit(out,op,a,b,c); total++;
        }
    }
    /* FMA cancellation that distinguishes fused from rounded multiply+add. */
    emit(out,3,0x3f800001,0x3f7ffffe,0xbf800000); total++;
    for(unsigned op=8;op<16;op++) {emit(out,op,0x3f800000,0,0);total++;}
    if(fclose(out)) return 5;
    printf("HOST_REFERENCE vectors=%u random_per_op=%u seed=6385f29b FE_TONEAREST\n",total,count);
    return 0;
}
