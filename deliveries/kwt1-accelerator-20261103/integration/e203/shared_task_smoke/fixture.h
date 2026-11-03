#ifndef KWT_TASK_FIXTURE_H
#define KWT_TASK_FIXTURE_H
#include <stdint.h>
int32_t fixture_x(uint32_t row, uint32_t k);
int32_t fixture_w(uint32_t k, uint32_t column);
int32_t fixture_bias(uint32_t column);
uint32_t fixture_convert(int64_t raw, uint32_t last);
uint32_t fixture_expected(uint32_t row, uint32_t column);
#endif
