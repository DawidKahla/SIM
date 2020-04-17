#include "PAW_Circle.h"

void PAW_Circle_show(PAW_Circle* const circle, const uint32_t buffer)
{
	if (!circle->is_filled)
	{
		PAW_Vector p = {4, {0.0f, -circle->radius, 0.0f}};
		for (float i = 0; i < 360; ++i)
		{
			PAW_Matrix rotation_matrix = {p.size};
			PAW_Matrix_to_rotation_matrix(&rotation_matrix, 1, 0, i);
			PAW_Vector temp = PAW_Matrix_mul_vec(&rotation_matrix, &p);

			uint32_t x = PAW_Vector_get_data(&temp, 0) + PAW_Vector_get_data(&circle->center, 0);
			uint32_t y = PAW_Vector_get_data(&temp, 1) + PAW_Vector_get_data(&circle->center, 1);
			uint32_t color = circle->color;
			PAW_Write_To_Buffer(buffer, x, y, color);
		}
	}
	else
	{
		PAW_Vector p = {3, {0.0f, -circle->radius, 0.0f}};
		for (float i = 0; i < 360; i += 2)
		{
			PAW_Matrix rotation_matrix = {4};
			PAW_Matrix_to_rotation_matrix(&rotation_matrix, 1, 0, i);
			PAW_Vector temp = PAW_Matrix_mul_vec(&rotation_matrix, &p);

			PAW_Vector first = {3, {
								PAW_Vector_get_data(&temp, 0) + PAW_Vector_get_data(&circle->center, 0),
								PAW_Vector_get_data(&temp, 1) + PAW_Vector_get_data(&circle->center, 1),
								0.0f}};

			PAW_Vector second = {3, {
								PAW_Vector_get_data(&circle->center, 0),
								PAW_Vector_get_data(&circle->center, 1),
								0.0f}};

			PAW_Line line = {circle->is_filled, circle->color, first, second};
			PAW_Line_show(&line, buffer);
		}
	}
}

void PAW_Circle_drawOnTexture(PAW_Circle* const circle, PAW_Texture* texture)
{
	if (!circle->is_filled)
		{
			PAW_Vector p = {4, {0.0f, -circle->radius, 0.0f, 0.0f}};
			for (float i = 0; i < 360; ++i)
			{
				PAW_Matrix rotation_matrix = {p.size};
				PAW_Matrix_to_rotation_matrix(&rotation_matrix, 1, 0, i);
				PAW_Vector temp = PAW_Matrix_mul_vec(&rotation_matrix, &p);

				*PAW_Texture_at(texture, PAW_Vector_get_data(&temp, 0) + PAW_Vector_get_data(&circle->center, 0),
						PAW_Vector_get_data(&temp, 1) + PAW_Vector_get_data(&circle->center, 1)) =
								circle->color;
			}
		}
		else
		{
			PAW_Vector p = {4, {0.0f, -circle->radius, 0.0f, 0.0f}};
			for (float i = 0; i < 360; i += 2)
			{
				PAW_Matrix rotation_matrix = {4};
				PAW_Matrix_to_rotation_matrix(&rotation_matrix, 1, 0, i);
				PAW_Vector temp = PAW_Matrix_mul_vec(&rotation_matrix, &p);

				PAW_Vector first = {3, {
									PAW_Vector_get_data(&temp, 0) + PAW_Vector_get_data(&circle->center, 0),
									PAW_Vector_get_data(&temp, 1) + PAW_Vector_get_data(&circle->center, 1),
									0.0f}};

				PAW_Vector second = {3, {
									PAW_Vector_get_data(&circle->center, 0),
									PAW_Vector_get_data(&circle->center, 1),
									0.0f}};

				PAW_Line line = {circle->color, circle->is_filled, first, second};
				PAW_Line_drawOnTexture(&line, texture);
			}
		}
}

void PAW_Circle_rotate(PAW_Circle* const circle, const PAW_Vector* const rotate_point,
		const int16_t degrees)
{
	PAW_Matrix rotation_matrix = {rotate_point->size};
	PAW_Matrix_to_rotation_matrix(&rotation_matrix, 1, 0, degrees);

	//position = rotation_matrix * (position - rotate_point) + rotate_point;
	PAW_Vector temp1 = PAW_Vector_sub(&circle->center, rotate_point);
	PAW_Vector temp2 = PAW_Matrix_mul_vec(&rotation_matrix, &temp1);
	PAW_Vector temp3 = PAW_Vector_add(&temp2, rotate_point);

	PAW_Vector_assign(&circle->center, &temp3);
}
void PAW_Circle_translate(PAW_Circle* const circle, const PAW_Vector* const translation)
{
	PAW_Vector_add_assign(&circle->center, translation);
}

void PAW_Circle_rotate_helper(PAW_Circle* const circle, const PAW_Matrix* const rotation_matrix)
{
	*PAW_Vector_at(&circle->center, 1) *= -1;
	*PAW_Vector_at(&circle->center, 2) *= -1;
	//center = rotation_matrix * center;
	circle->center = PAW_Matrix_mul_vec(rotation_matrix, &circle->center);
	*PAW_Vector_at(&circle->center, 1) *= -1;
	*PAW_Vector_at(&circle->center, 2) *= -1;
}
void PAW_Circle_projection_helper(PAW_Circle* const circle, const PAW_Matrix* const projection_matrix)
{
	*PAW_Vector_at(&circle->center, 1) *= -1;
	*PAW_Vector_at(&circle->center, 2) *= -1;
	//center = projection_matrix * center;
	circle->center = PAW_Matrix_mul_vec(projection_matrix, &circle->center);
}
void PAW_Circle_scale_helper(PAW_Circle* const circle, const float scale)
{
	PAW_Vector_mul_assign(&circle->center, scale);
	circle->radius *= scale;
}
