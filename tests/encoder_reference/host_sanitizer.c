#include "encoder_ref.h"
#include <fenv.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned stages;
static int failed;
static void observe(void *context,unsigned stage,const float *values,size_t rows,size_t cols) {
    (void)context;
    if (stage>=KWT_STAGE_COUNT) failed=1;
    for (size_t i=0;i<rows*cols;++i) if (!isfinite(values[i])) failed=1;
    ++stages;
}
int main(void) {
    if (fesetround(FE_TONEAREST)!=0) return 10;
    const size_t dims[3][3]={{1,1,1},{3,4,8},{99,64,256}};
    for (unsigned n=0;n<3;++n) {
        size_t m=dims[n][0],d=dims[n][1],h=dims[n][2];
        float *x=calloc(m*d,sizeof(float)),*w=calloc(kwt_weight_words(d,h),sizeof(float));
        float *y=calloc(m*d,sizeof(float));
        if (!x || !w || !y) return 11;
        stages=0;
        if (kwt_encoder_layer(m,d,h,x,w,y,observe,NULL)!=0) return 12;
        if (stages!=KWT_STAGE_COUNT || failed) return 13;
        for (size_t i=0;i<m*d;++i) if (y[i]!=0.0f) return 14;
        free(x);free(w);free(y);
    }
    puts("UBSan host dimensions 1x1x1,3x4x8,99x64x256 PASS");
    return 0;
}
