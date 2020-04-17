#include "PAW_Vector.h"

size_t PAW_Vector_get_size(const PAW_Vector* const vector)
{
	return vector->size;
}

float PAW_Vector_get_data(const PAW_Vector* const vector, const size_t index)
{
	if (index < vector->size)
	{
		return vector->data[index];
	}
	else
	{
		return 0.0f;
	}
}

void PAW_Vector_set_data(PAW_Vector* const vector, const size_t index, const float value)
{
	if (index < vector->size)
	{
		vector->data[index] = value;
	}
}

void PAW_Vector_randomize(PAW_Vector* const vector)
{
	for (size_t i = 0; i < vector->size; ++i)
	{
		vector->data[i] = rand_float(0.0f, 255.0f);
	}
}

float* PAW_Vector_at(PAW_Vector* const vector, const size_t index)
{
	if (vector->data == NULL)
	{
		fprintf( stderr, "Vector is not allocated\n");
	}
	else if (index < vector->size)
	{
		return &(vector->data[index]);
	}
	else
	{
		fprintf(stderr, "Invalid index\n");
	}
	return NULL;
}

boolean PAW_Vector_eq(const PAW_Vector* const first, const PAW_Vector* const second)
{
	if (first->size != second->size)
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i < first->size; ++i)
		{
			if (first->data[i] != second->data[i])
			{
				return false;
			}
		}
	}

	return true;
}

boolean PAW_Vector_neq(const PAW_Vector* const first, const PAW_Vector* const second)
{
	return !PAW_Vector_eq(first, second);
}

PAW_Vector PAW_Vector_add(const PAW_Vector* const first, const PAW_Vector* const second)
{
	PAW_Vector result = {first->size};
	if (first->size != second->size)
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			result.data[i] = first->data[i] + second->data[i];
		}

		return result;
	}
}

PAW_Vector PAW_Vector_sub(const PAW_Vector* const first, const PAW_Vector* const second)
{
	PAW_Vector result = {first->size};
	if (first->size != second->size)
	{
		return result;
	}
	else
	{
		result.size = first->size;

		for (size_t i = 0; i < result.size; ++i)
		{
			result.data[i] = first->data[i] - second->data[i];
		}

		return result;
	}
}

PAW_Vector PAW_Vector_inv(const PAW_Vector* const vector)
{
	PAW_Vector result = {vector->size};

	for (size_t i = 0; i < vector->size; ++i)
	{
		result.data[i] = vector->data[i] * -1.0f;
	}

	return result;
}

PAW_Vector PAW_Vector_mul(const PAW_Vector* const first, const float second)
{
	PAW_Vector result = {first->size};

	for (size_t i = 0; i < first->size; ++i)
	{
		result.data[i] = first->data[i] * second;
	}

	return result;
}

PAW_Vector PAW_Vector_div(const PAW_Vector* const first, const float second)
{
	PAW_Vector result = {first->size};

	for (size_t i = 0; i < first->size; ++i)
	{
		result.data[i] = first->data[i] / second;
	}

	return result;
}

PAW_Vector* PAW_Vector_assign(PAW_Vector* const first, const PAW_Vector* const second)
{
	first->size = second->size;

	for (size_t i = 0; i < first->size; ++i)
	{
		first->data[i] = second->data[i];
	}
	
	return first;
}

PAW_Vector* PAW_Vector_add_assign(PAW_Vector* const first, const PAW_Vector* const second)
{
	if (first->size == second->size)
	{
		for (size_t i = 0; i < first->size; ++i)
		{
			first->data[i] += second->data[i];
		}
	}

	return first;
}

PAW_Vector* PAW_Vector_sub_assign(PAW_Vector* const first, const PAW_Vector* const second)
{
	if (first->size == second->size)
	{
		for (size_t i = 0; i < first->size; ++i)
		{
			first->data[i] -= second->data[i];
		}
	}

	return first;
}

PAW_Vector* PAW_Vector_mul_assign(PAW_Vector* const first, const float second)
{
	for (size_t i = 0; i < first->size; ++i)
	{
		first->data[i] *= second;
	}

	return first;
}

PAW_Vector* PAW_Vector_div_assign(PAW_Vector* const first, const float second)
{
	for (size_t i = 0; i < first->size; ++i)
	{
		first->data[i] /= second;
	}

	return first;
}

boolean PAW_Vector_is_small(const PAW_Vector* const vector, const float precision)
{
	for (size_t i = 0; i < vector->size; ++i)
	{
		if (abs(vector->data[i]) >= precision)
		{
			return false;
		}
	}

	return true;
}

boolean PAW_Vector_is_finite(const PAW_Vector* const vector)
{
	for (size_t i = 0; i < vector->size; ++i)
	{
		if (!is_float_finite(vector->data[i]))
		{
			return false;
		}
	}
	return true;
}

float PAW_Vector_length(const PAW_Vector* const vector)
{
	float r_value = 0.0f;

	for (size_t i = 0; i < vector->size; ++i)
	{
		r_value += pow(vector->data[i], 2);
	}

	return sqrt(r_value);
}

PAW_Vector PAW_Vector_versor(const PAW_Vector* const vector, const float precision)
{
	if (PAW_Vector_is_small(vector, precision))
	{
		PAW_Vector vec = {4};
		return vec;
	}
	else
	{
		return PAW_Vector_div(vector, PAW_Vector_length(vector));
	}
}

PAW_Vector PAW_Vector_relative_error(const PAW_Vector* const first,
		const PAW_Vector* const second, float precision)
{
	if (first->size != second->size)
	{
		PAW_Vector vec = {0};
		return vec;
	}
	else
	{
		PAW_Vector result = {first->size};

		for (size_t i = 0; i < result.size; ++i)
		{
			result.data[i] = relative_error_float(first->data[i], second->data[i], precision);
		}

		return result;
	}
}

void PAW_Vector_swap(PAW_Vector* const first, PAW_Vector* const second)
{
	PAW_Vector temp = *first;
	*first = *second;
	*second = temp;
}

FILE* PAW_Vector_print(FILE* out, const PAW_Vector* const vector)
{
	if (vector->size > 0)
	{
		fprintf(out,"[");
		for (size_t i = 0; i < vector->size; ++i)
		{
			if (i != vector->size - 1)
			{
				fprintf(out, "%f, ", vector->data[i]);
			}
			else
			{
				fprintf(out, "%f]\n", vector->data[i]);
			}
		}
	}
	return out;
}
