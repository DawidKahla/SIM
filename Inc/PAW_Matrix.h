#ifndef PAW_MATRIX_H
#define PAW_MATRIX_H

#include "PAW_Vector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	size_t size;
	float data[4][4];
}PAW_Matrix;

float PAW_Matrix_get_data(const PAW_Matrix* const matrix,
		const size_t row, const size_t column);
void PAW_Matrix_set_data(PAW_Matrix* const matrix,
		const size_t row, const size_t column, const float value);
size_t PAW_Matrix_get_size(const PAW_Matrix* const matrix);
void PAW_Matrix_randomize(PAW_Matrix* const matrix);
void PAW_Matrix_diagonal(PAW_Matrix* const matrix, const float value);

PAW_Matrix PAW_Matrix_add(const PAW_Matrix* const first, const PAW_Matrix* const second);
PAW_Matrix PAW_Matrix_sub(const PAW_Matrix* const first, const PAW_Matrix* const second);
PAW_Matrix PAW_Matrix_inv(const PAW_Matrix* const matrix);
PAW_Matrix PAW_Matrix_mul_num(const PAW_Matrix* const first, const float second);
PAW_Matrix PAW_Matrix_div_num(const PAW_Matrix* const first, const float second);

PAW_Vector PAW_Matrix_mul_vec(const PAW_Matrix* const first, const PAW_Vector* const second);
PAW_Matrix PAW_Matrix_mul_mat(const PAW_Matrix* const first, const PAW_Matrix* const second);
PAW_Matrix PAW_Matrix_inverse(const PAW_Matrix* const matrix);

PAW_Matrix* PAW_Matrix_assign(PAW_Matrix* const first, const PAW_Matrix* const second);
PAW_Matrix* PAW_Matrix_add_assign(PAW_Matrix* const first, const PAW_Matrix* const second);
PAW_Matrix* PAW_Matrix_sub_assign(PAW_Matrix* const first, const PAW_Matrix* const second);
PAW_Matrix* PAW_Matrix_mul_num_assign(PAW_Matrix* const first, const float second);
PAW_Matrix* PAW_Matrix_div_num_assign(PAW_Matrix* const first, const float second);

boolean PAW_Matrix_eq(const PAW_Matrix* const first, const PAW_Matrix* const second);
boolean PAW_Matrix_neq(const PAW_Matrix* const first, const PAW_Matrix* const second);

float* PAW_Matrix_at(PAW_Matrix* const matrix, const size_t index1, const size_t index2);

void PAW_Matrix_to_rotation_matrix(PAW_Matrix* const matrix,
		const size_t i, const size_t j, const float deg);
PAW_Matrix PAW_Matrix_givens(const PAW_Matrix* const matrix,
		const size_t i, const size_t j, const float precision);

PAW_Matrix relative_error(const PAW_Matrix* const first, const PAW_Matrix* const second,
		const float precision);
FILE* PAW_Matrix_print(FILE* out, const PAW_Matrix* const matrix);

#ifdef __cplusplus
}
#endif

#endif //PAW_MATRIX_H
