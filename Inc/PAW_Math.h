#ifndef PAW_MATH_H
#define PAW_MATH_H

#define boolean char
#define false 0
#define true 1

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

float min(const float a,const float b);
float max(const float a, const float b);

float relative_error_float(const float a, const float b, const float precision);

boolean is_float_finite(const float a);
boolean is_nan(const float a);
float m_hypot(const float a, const float b);
float rand_float(const float from, const float to);
int rand_int(const int from, const int to);

void swap(float* a, float* b);
int int_part(const float a);
float frac_part(const float a);
int round_float(const float a);

#ifdef __cplusplus
}
#endif

#endif //PAW_MATH_H
