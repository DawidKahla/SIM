#include "PAW_Square.h"

void PAW_Square_show(PAW_Square* const square, uint32_t buffer)
{
	PAW_Vector temp = PAW_Vector_add(&square->corner, &square->side[0]);
	PAW_Vector corners[] = {square->corner,
			temp,
			PAW_Vector_add(&temp, &square->side[1]),
			PAW_Vector_add(&square->corner, &square->side[1])
	};

	PAW_Line sides[] = {{0xff000000, 1, corners[0], corners[1]},
			{0xff000000, 1, corners[1], corners[2]},
			{0xff000000, 1, corners[2], corners[3]},
			{0xff000000, 1, corners[3], corners[0]}
	};

	for (size_t i = 0; i < 4; ++i)
	{
		PAW_Line_show(&sides[i], buffer);
	}
	if (square->has_texture)
	{
		PAW_Vector directions[2] = { PAW_Vector_div(&square->side[0], square->texture.height),
				PAW_Vector_div(&square->side[1], square->texture.width)
		};
		for (float i = 0; i < square->texture.height; ++i)
		{
			for (float j = 0; j < square->texture.width; ++j)
			{
				PAW_Vector increment[2] = {
					PAW_Vector_mul(&directions[0], i),
					PAW_Vector_mul(&directions[1], j)
				};
				PAW_Vector temp = PAW_Vector_add(&square->corner, &increment[0]);
				PAW_Vector position = PAW_Vector_add(&temp, &increment[1]);
				uint32_t x = PAW_Vector_get_data(&position, 0);
				uint32_t y = PAW_Vector_get_data(&position, 1);
				uint32_t color = *PAW_Texture_at(&square->texture, i, j);
				PAW_Write_To_Buffer(buffer, x, y, color);
			}
		}
	}
}

void PAW_Square_rotate(PAW_Square* const square, const PAW_Vector* const rotate_point,
		const int16_t degrees)
{
	PAW_Matrix rotation_matrix = {rotate_point->size};
	PAW_Matrix_to_rotation_matrix(&rotation_matrix, 1, 0, degrees);

	//position = rotation_matrix * (position - rotate_point) + rotate_point;
	PAW_Vector temp1 = PAW_Vector_sub(&square->corner, rotate_point);
	PAW_Vector temp2 = PAW_Matrix_mul_vec(&rotation_matrix, &temp1);
	PAW_Vector temp3 = PAW_Vector_add(&temp2, rotate_point);
	PAW_Vector_assign(&square->corner, &temp3);
	for (size_t i = 0; i < 2; ++i)
	{
		PAW_Vector temp1 = PAW_Vector_sub(&square->side[i], rotate_point);
		PAW_Vector temp2 = PAW_Matrix_mul_vec(&rotation_matrix, &temp1);
		PAW_Vector temp3 = PAW_Vector_add(&temp2, rotate_point);
		PAW_Vector_assign(&square->side[i], &temp3);
	}
}
void PAW_Square_translate(PAW_Square* const square, const PAW_Vector* const translation)
{
	PAW_Vector_add_assign(&square->corner, translation);
}

void PAW_Square_rotate_helper(PAW_Square* const square, const PAW_Matrix* const rotation_matrix)
{

	*PAW_Vector_at(&square->corner, 1) *= -1;
	*PAW_Vector_at(&square->corner, 2) *= -1;
	//center = rotation_matrix * center;
	square->corner = PAW_Matrix_mul_vec(rotation_matrix, &square->corner);
	*PAW_Vector_at(&square->corner, 1) *= -1;
	*PAW_Vector_at(&square->corner, 2) *= -1;
	for (size_t i = 0; i < 2; ++i)
	{
		*PAW_Vector_at(&square->side[i], 1) *= -1;
		*PAW_Vector_at(&square->side[i], 2) *= -1;
		//center = rotation_matrix * center;
		square->side[i] = PAW_Matrix_mul_vec(rotation_matrix, &square->side[i]);
		*PAW_Vector_at(&square->side[i], 1) *= -1;
		*PAW_Vector_at(&square->side[i], 2) *= -1;
	}
}
void PAW_Square_projection_helper(PAW_Square* const square, const PAW_Matrix* const projection_matrix)
{
	*PAW_Vector_at(&square->corner, 1) *= -1;
	*PAW_Vector_at(&square->corner, 2) *= -1;
	//center = projection_matrix * center;
	square->corner = PAW_Matrix_mul_vec(projection_matrix, &square->corner);

	for (size_t i = 0; i < 2; ++i)
	{
		*PAW_Vector_at(&square->side[i], 1) *= -1;
		*PAW_Vector_at(&square->side[i], 2) *= -1;
		//center = rotation_matrix * center;
		square->side[i] = PAW_Matrix_mul_vec(projection_matrix, &square->side[i]);
	}
}
void PAW_Square_scale_helper(PAW_Square* const square, const float scale)
{
	PAW_Vector_mul_assign(&square->side[0], scale);
	PAW_Vector_mul_assign(&square->side[1], scale);
}
