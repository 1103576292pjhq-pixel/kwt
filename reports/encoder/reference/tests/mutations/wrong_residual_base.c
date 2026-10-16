#include "encoder_ref.h"
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

_Static_assert(sizeof(float)==4 && FLT_RADIX==2 && FLT_MANT_DIG==24,
               "The verification model requires IEEE binary32 float");

static float from_bits(uint32_t bits) { float x; memcpy(&x,&bits,4); return x; }
size_t kwt_weight_words(size_t d, size_t h) { return 4*d*d + 2*d*h + h + 6*d; }

/* Exact expression order is part of work/formal_seven_design.md. No fitted
 * coefficients, libm exp, host matrix multiply or neural runtime is used. */
float kwt_exp_neg(float x) {
    static const float c[9]={1.0f,1.0f,0.5f,1.0f/6.0f,1.0f/24.0f,
                            1.0f/120.0f,1.0f/720.0f,1.0f/5040.0f,1.0f/40320.0f};
    if (!isfinite(x) || x>0.0f) return from_bits(UINT32_C(0x7fc00000));
    if (x<=-80.0f) return 0.0f;
    if (x==0.0f) return 1.0f;
    float scaled=x*1.4426950408889634f;
    int32_t n=(int32_t)nearbyintf(scaled);
    float nf=(float)n;
    float r=fmaf(-nf,0.693145751953125f,x);
    r=fmaf(-nf,1.428606765330187e-6f,r);
    float p=c[8];
    for (int k=7;k>=0;--k) p=fmaf(p,r,c[k]);
    float power=from_bits((uint32_t)(n+127)<<23);
    return p*power;
}

float kwt_gelu(float x) {
    if (!isfinite(x)) return from_bits(UINT32_C(0x7fc00000));
    if (fabsf(x)>=10.0f) return signbit(x)?-0.0f:x;
    float a=x*x;
    float b=a*x;
    float c=fmaf(0.044715f,b,x);
    float u=0.7978845608028654f*c;
    float neg=-2.0f*fabsf(u);
    float e=kwt_exp_neg(neg);
    float den=1.0f+e;
    if (signbit(x)) {
        float numerator=x*e;
        return numerator/den;
    }
    return x/den;
}

static void dense(size_t m,size_t in,size_t out,const float*x,const float*w,
                  const float*b,float*y) {
    for (size_t i=0;i<m;++i) for (size_t j=0;j<out;++j) {
        float acc=0.0f;
        for (size_t k=0;k<in;++k) acc=fmaf(x[i*in+k],w[k*out+j],acc);
        y[i*out+j]=b?acc+b[j]:acc;
    }
}

static void norm(size_t m,size_t d,const float*x,const float*gamma,
                 const float*beta,float*y) {
    float inv_d=1.0f/(float)d;
    for (size_t i=0;i<m;++i) {
        float sum=0.0f;
        for (size_t j=0;j<d;++j) sum=sum+x[i*d+j];
        float mean=sum*inv_d;
        float center[64];
        float varsum=0.0f;
        for (size_t j=0;j<d;++j) {
            center[j]=x[i*d+j]-mean;
            varsum=fmaf(center[j],center[j],varsum);
        }
        float variance=varsum*inv_d;
        float shifted=variance+1.0e-6f;
        float std=sqrtf(shifted);
        float invstd=1.0f/std;
        for (size_t j=0;j<d;++j) {
            float normalized=center[j]*invstd;
            y[i*d+j]=fmaf(normalized,gamma[j],beta[j]);
        }
    }
}

int kwt_encoder_layer(size_t m,size_t d,size_t h,const float*x,const float*w,
                      float*y,kwt_stage_callback cb,void*ctx) {
    if (!m || m>99 || !d || d>64 || !h || h>256 || !x || !w || !y) return -1;
    const float *wq=w, *wk=wq+d*d, *wv=wk+d*d, *wo=wv+d*d;
    const float *bo=wo+d*d,*g1=bo+d,*b1=g1+d,*w1=b1+d,*bh=w1+d*h;
    const float *w2=bh+h,*b2=w2+h*d,*g2=b2+d,*bn2=g2+d;
    float *s[KWT_STAGE_COUNT]={0};
    size_t cols[KWT_STAGE_COUNT]={d,d,d,m,m,d,d,d,d,h,h,d,d,d};
    for (unsigned k=0;k<KWT_STAGE_COUNT;++k) {
        s[k]=calloc(m*cols[k],sizeof(float));
        if (!s[k]) { for (unsigned j=0;j<k;++j) free(s[j]); return -2; }
    }
    dense(m,d,d,x,wq,NULL,s[KWT_Q]);
    dense(m,d,d,x,wk,NULL,s[KWT_K]);
    dense(m,d,d,x,wv,NULL,s[KWT_V]);
    for (size_t i=0;i<m;++i) {
        for (size_t j=0;j<m;++j) {
            float acc=0.0f;
            for (size_t k=0;k<d;++k) acc=fmaf(s[KWT_Q][i*d+k],s[KWT_K][j*d+k],acc);
            s[KWT_SCORES][i*m+j]=acc*0.125f;
        }
        float maximum=s[KWT_SCORES][i*m];
        for (size_t j=1;j<m;++j) if (s[KWT_SCORES][i*m+j]>maximum) maximum=s[KWT_SCORES][i*m+j];
        float sum=0.0f;
        for (size_t j=0;j<m;++j) {
            float delta=s[KWT_SCORES][i*m+j]-maximum;
            s[KWT_PROB][i*m+j]=kwt_exp_neg(delta);
            sum=sum+s[KWT_PROB][i*m+j];
        }
        for (size_t j=0;j<m;++j) s[KWT_PROB][i*m+j]=s[KWT_PROB][i*m+j]/sum;
        for (size_t k=0;k<d;++k) {
            float acc=0.0f;
            for (size_t j=0;j<m;++j) acc=fmaf(s[KWT_PROB][i*m+j],s[KWT_V][j*d+k],acc);
            s[KWT_CONTEXT][i*d+k]=acc;
        }
    }
    dense(m,d,d,s[KWT_CONTEXT],wo,bo,s[KWT_ATTN]);
    for (size_t k=0;k<m*d;++k) s[KWT_R1][k]=x[k]+s[KWT_ATTN][k];
    norm(m,d,s[KWT_R1],g1,b1,s[KWT_N1]);
    dense(m,d,h,s[KWT_N1],w1,bh,s[KWT_FFN1]);
    for (size_t k=0;k<m*h;++k) s[KWT_GELU][k]=kwt_gelu(s[KWT_FFN1][k]);
    dense(m,h,d,s[KWT_GELU],w2,b2,s[KWT_FFN2]);
    for (size_t k=0;k<m*d;++k) s[KWT_R2][k]=x[k]+s[KWT_FFN2][k];
    norm(m,d,s[KWT_R2],g2,bn2,s[KWT_Y]);
    memcpy(y,s[KWT_Y],m*d*sizeof(float));
    int rc=0;
    for (unsigned k=0;k<KWT_STAGE_COUNT;++k) {
        for (size_t j=0;j<m*cols[k];++j) if (!isfinite(s[k][j])) rc=-3;
        if (cb) cb(ctx,k,s[k],m,cols[k]);
        free(s[k]);
    }
    return rc;
}

void kwt_classifier(size_t d,size_t n,const float*x,const float*w,const float*b,float*y) {
    dense(1,d,n,x,w,b,y);
}
