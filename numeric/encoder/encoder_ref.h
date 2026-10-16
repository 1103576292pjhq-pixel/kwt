#ifndef KWT_ENCODER_REF_H
#define KWT_ENCODER_REF_H
#include <stddef.h>

/* Host verification model only. Production E203 firmware does not call this. */
enum kwt_stage {
    KWT_Q, KWT_K, KWT_V, KWT_SCORES, KWT_PROB, KWT_CONTEXT,
    KWT_ATTN, KWT_R1, KWT_N1, KWT_FFN1, KWT_GELU, KWT_FFN2,
    KWT_R2, KWT_Y, KWT_STAGE_COUNT
};
typedef void (*kwt_stage_callback)(void *context, unsigned stage,
                                 const float *values, size_t rows, size_t cols);
size_t kwt_weight_words(size_t d, size_t h);
float kwt_exp_neg(float x);
float kwt_gelu(float x);
int kwt_encoder_layer(size_t m, size_t d, size_t h, const float *input,
                      const float *packed, float *output,
                      kwt_stage_callback callback, void *context);
void kwt_classifier(size_t d, size_t classes, const float *cls,
                    const float *kernel, const float *bias, float *logits);
#endif
