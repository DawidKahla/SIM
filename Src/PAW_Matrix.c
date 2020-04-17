#include "PAW_Matrix.h"

float PAW_Matrix_get_data(const PAW_Matrix* const matrix, const size_t row, const size_t column)
{
	return matrix->data[row][column];
}

void PAW_Matrix_set_data(PAW_Matrix* const matrix,
			const size_t row, const size_t column, const float value)
{
	matrix->data[row][column] = value;
}

size_t PAW_Matrix_get_size(const PAW_Matrix* const matrix)
{
	return matrix->size;
}

void PAW_Matrix_randomize(PAW_Matrix* const matrix)
{
	for (size_t i = 0; i < matrix->size; ++i)
	{
		for (size_t j = 0; j < matrix->size; ++j)
		{
			PAW_Matrix_set_data(matrix, i, j, rand_float(0.0f, 255.0f));
		}
	}
}

void PAW_Matrix_diagonal(PAW_Matrix* const matrix, const float value)
{
	for (size_t i = 0; i < matrix->size; ++i)
	{
		PAW_Matrix_set_data(matrix, i, i, value);
	}
}

PAW_Matrix PAW_Matrix_add(const PAW_Matrix* const first, const PAW_Matrix* const second)
{
	PAW_Matrix result = {first->size};
	if (first->size != second->size)
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			for (size_t j = 0; j < result.size; ++j)
			{
				PAW_Matrix_set_data(&result, i, j,
						PAW_Matrix_get_data(first, i, j) + PAW_Matrix_get_data(second, i, j));
			}
		}
		return result;
	}
}

PAW_Matrix PAW_Matrix_sub(const PAW_Matrix* const first, const PAW_Matrix* const second)
{
	PAW_Matrix result = {first->size};
	if (first->size != second->size)
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			for (size_t j = 0; j < result.size; ++j)
			{
				PAW_Matrix_set_data(&result, i, j,
						PAW_Matrix_get_data(first, i, j) - PAW_Matrix_get_data(second, i, j));
			}
		}
		return result;
	}
}

PAW_Matrix PAW_Matrix_inv(const PAW_Matrix* const matrix)
{
	PAW_Matrix result = {matrix->size};

	for (size_t i = 0; i < result.size; ++i)
	{
		for (size_t j = 0; j < result.size; ++j)
		{
			PAW_Matrix_set_data(&result, i, j, PAW_Matrix_get_data(matrix, i, j) *-1.0f);
		}
	}

	return result;
}

PAW_Matrix PAW_Matrix_mul_num(const PAW_Matrix* const first, const float second)
{
	PAW_Matrix result = {first->size};

	for (size_t i = 0; i < result.size; ++i)
	{
		for (size_t j = 0; j < result.size; ++j)
		{
			PAW_Matrix_set_data(&result, i, j, PAW_Matrix_get_data(first, i, j) * second);
		}
	}
	return result;
}


PAW_Matrix PAW_Matrix_div_num(const PAW_Matrix* const first, const float second)
{
	PAW_Matrix result = {first->size};

	for (size_t i = 0; i < result.size; ++i)
	{
		for (size_t j = 0; j < result.size; ++j)
		{
			PAW_Matrix_set_data(&result, i, j, PAW_Matrix_get_data(first, i, j) / second);
		}
	}
	return result;
}

PAW_Vector PAW_Matrix_mul_vec(const PAW_Matrix* const first, const PAW_Vector* const second)
{
	PAW_Vector result = {first->size};
	if (first->size != PAW_Vector_get_size(second))
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			result.data[i] = 0;
			for (size_t j = 0; j < result.size; ++j)
			{
				result.data[i] += PAW_Matrix_get_data(first, i, j) * PAW_Vector_get_data(second, j);
			}
		}
		return result;
	}
}

PAW_Matrix PAW_Matrix_mul_mat(const PAW_Matrix* const first, const PAW_Matrix* const second)
{
	PAW_Matrix result = {first->size};
	if (first->size != second->size)
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			for (size_t j = 0; j < result.size; ++j)
			{
				float temp = 0.0f;
				for (size_t a = 0; a < result.size; ++a)
				{
					temp += PAW_Matrix_get_data(first, i, a) * PAW_Matrix_get_data(second, a, j);
				}
				PAW_Matrix_set_data(&result, i, j, temp);
			}
		}
		return result;
	}
}

PAW_Matrix PAW_Matrix_inverse(const PAW_Matrix* const matrix)
{
	double inv[16], det, m[16];

	for (size_t i = 0, j = 0; i < 16; ++i)
	{
		if ((i + 1) % 5 == 0)
		{
			++j;
		}
		m[i] = PAW_Matrix_get_data(matrix, j, i % 4);

	}

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	PAW_Matrix result = {0};

	if (det == 0)
		return result;

	det = 1.0 / det;
	/*
	for (i = 0; i < 16; i++)
		invOut[i] = inv[i] * det;
		*/

	result.size = 4;

	for (size_t i = 0, j=0; i < 16; ++i)
	{
		if ((i + 1) % 5 == 0)
		{
			++j;
		}
		PAW_Matrix_set_data(&result, j, i % 4, inv[i] * det);
	}
	return result;
}

PAW_Matrix* PAW_Matrix_assign(PAW_Matrix* const first, const PAW_Matrix* const second)
{
	first->size = second->size;
	for (size_t i = 0; i < first->size; ++i)
	{
		for (size_t j = 0; j < first->size; ++j)
		{
			PAW_Matrix_set_data(first, i, j, PAW_Matrix_get_data(second, i, j));
		}
	}

	return first;
}

PAW_Matrix* PAW_Matrix_add_assign(PAW_Matrix* const first, const PAW_Matrix* const second)
{
	if (first->size == second->size)
	{
		for (size_t i = 0; i < first->size; ++i)
		{
			for (size_t j = 0; j < first->size; ++j)
			{
				PAW_Matrix_set_data(first, i, j,
						PAW_Matrix_get_data(first, i, j) + PAW_Matrix_get_data(second, i, j));
			}
		}
	}

	return first;
}

PAW_Matrix* PAW_Matrix_sub_assign(PAW_Matrix* const first, const PAW_Matrix* const second)
{
	if (first->size == second->size)
	{
		for (size_t i = 0; i < first->size; ++i)
		{
			for (size_t j = 0; j < first->size; ++j)
			{
				PAW_Matrix_set_data(first, i, j,
						PAW_Matrix_get_data(first, i, j) - PAW_Matrix_get_data(second, i, j));
			}
		}
	}

	return first;
}

PAW_Matrix* PAW_Matrix_mul_num_assign(PAW_Matrix* const first, const float second)
{
	for (size_t i = 0; i < first->size; ++i)
	{
		for (size_t j = 0; j < first->size; ++j)
		{
			PAW_Matrix_set_data(first, i, j,
				PAW_Matrix_get_data(first, i, j) * second);
		}
	}

	return first;
}

PAW_Matrix* PAW_Matrix_div_num_assign(PAW_Matrix* const first, const float second)
{
	for (size_t i = 0; i < first->size; ++i)
	{
		for (size_t j = 0; j < first->size; ++j)
		{
			PAW_Matrix_set_data(first, i, j,
				PAW_Matrix_get_data(first, i, j) / second);
		}
	}

	return first;
}

boolean PAW_Matrix_eq(const PAW_Matrix* const first, const PAW_Matrix* const second)
{
	if (first->size != second->size)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < first->size; ++i)
		{
			for (size_t j = 0; j < first->size; ++j)
			{
				if (PAW_Matrix_get_data(first, i, j) != PAW_Matrix_get_data(second, i, j))
				{
					return false;
				}
			}
		}
		return true;
	}
}

boolean PAW_Matrix_neq(const PAW_Matrix* const first, const PAW_Matrix* const second)
{
	return !(PAW_Matrix_eq(first, second));
}

float* PAW_Matrix_at(PAW_Matrix* const matrix, const size_t index1, const size_t index2)
{
	return &matrix->data[index1][index2];
}

void PAW_Matrix_to_rotation_matrix(PAW_Matrix* const matrix,
			const size_t i, const size_t j, const float deg)
{
	if (i < matrix->size && j < matrix->size)
	{
		float rad = 3.1415f * deg / 180.0f;

		PAW_Matrix_diagonal(matrix, 1.0f);

		PAW_Matrix_set_data(matrix, i, i, cos(rad));
		PAW_Matrix_set_data(matrix, i, j, sin(rad));
		PAW_Matrix_set_data(matrix, j, i, -sin(rad));
		PAW_Matrix_set_data(matrix, j, j, cos(rad));
	}
}

PAW_Matrix PAW_Matrix_givens(const PAW_Matrix* const matrix,
			const size_t i, const size_t j, const float precision)
{
	PAW_Matrix result = {matrix->size};

	PAW_Matrix_diagonal(&result, 1.0f);

	if(abs(PAW_Matrix_get_data(matrix, i, j)) < precision)
	{
		return result;
	}
	else
	{
		const float r = hypot(PAW_Matrix_get_data(matrix, i, i),
				PAW_Matrix_get_data(matrix, j, j));
		const float c = PAW_Matrix_get_data(matrix, i, i) / r;
		const float s = PAW_Matrix_get_data(matrix, j, j) / r;

		PAW_Matrix_set_data(&result, i, i, c);
		PAW_Matrix_set_data(&result, i, j, s);
		PAW_Matrix_set_data(&result, j, i, -s);
		PAW_Matrix_set_data(&result, j, j, c);

		return result;
	}
}

PAW_Matrix relative_error(const PAW_Matrix* const first, const PAW_Matrix* const second,
			const float precision)
{
	PAW_Matrix result = {first->size};
	if (first->size != second->size)
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			for (size_t j = 0; j < result.size; ++j)
			{
				PAW_Matrix_set_data(&result, i, j,
						relative_error_float(PAW_Matrix_get_data(first, i, j),
						PAW_Matrix_get_data(second, i, j), precision));
			}
		}
		return result;
	}
}

FILE* PAW_Matrix_print(FILE* out, const PAW_Matrix* const matrix)
{
	for (size_t i = 0; i < matrix->size; ++i)
	{
		fprintf(out,"{");
		for (size_t j = 0; j < matrix->size; ++j)
		{
			if (j != matrix->size - 1)
			{
				fprintf(out, "%f| ", PAW_Matrix_get_data(matrix, i, j));
			}
			else
			{
				fprintf(out, "%f", PAW_Matrix_get_data(matrix, i, j));
			}
		}
		fprintf(out,"}\n");
	}
	return out;
}
