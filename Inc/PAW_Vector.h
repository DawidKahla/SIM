#ifndef PAW_Vector_H
#define PAW_Vector_H

#include <stdio.h>
#include <stdlib.h>

#include "PAW_Math.h"

typedef struct PAW_Vector
{
	size_t size;
	float data[4];
}PAW_Vector;

size_t PAW_Vector_get_size(const PAW_Vector* const vector);
float PAW_Vector_get_data(const PAW_Vector* const vector, const size_t index);
void PAW_Vector_set_data(PAW_Vector* const vector, const size_t index, const float value);

void PAW_Vector_randomize(PAW_Vector* const vector);

float* PAW_Vector_at(PAW_Vector* const vector, const size_t index);

boolean PAW_Vector_eq(const PAW_Vector* const first, const PAW_Vector* const second);
boolean PAW_Vector_neq(const PAW_Vector* const first, const PAW_Vector* const second);

PAW_Vector PAW_Vector_add(const PAW_Vector* const first, const PAW_Vector* const second);
PAW_Vector PAW_Vector_sub(const PAW_Vector* const first, const PAW_Vector* const second);
PAW_Vector PAW_Vector_inv(const PAW_Vector* const vector);
PAW_Vector PAW_Vector_mul(const PAW_Vector* const first, const float second);
PAW_Vector PAW_Vector_div(const PAW_Vector* const first, const float second);
PAW_Vector* PAW_Vector_assign(PAW_Vector* const first, const PAW_Vector* const second);
PAW_Vector* PAW_Vector_add_assign(PAW_Vector* const first, const PAW_Vector* const second);
PAW_Vector* PAW_Vector_sub_assign(PAW_Vector* const first, const PAW_Vector* const second);
PAW_Vector* PAW_Vector_mul_assign(PAW_Vector* const first, const float second);
PAW_Vector* PAW_Vector_div_assign(PAW_Vector* const first, const float second);

boolean PAW_Vector_is_small(const PAW_Vector* const vector, const float precision);
boolean PAW_Vector_is_finite(const PAW_Vector* const vector);
float PAW_Vector_length(const PAW_Vector* const vector);
PAW_Vector PAW_Vector_versor(const PAW_Vector* const vector, const float precision);

PAW_Vector PAW_Vector_relative_error(const PAW_Vector* const first,
		const PAW_Vector* const second, float precision);
void PAW_Vector_swap(PAW_Vector* const first, PAW_Vector* const second);
FILE* PAW_Vector_print(FILE* out, const PAW_Vector* const vector);

#ifdef __cplusplus
}
#endif

#endif //PAW_Vector_H
