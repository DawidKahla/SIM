#include "PAW_Point.h"

void PAW_Point_change_color(PAW_Point* const point, const uint32_t n_color){
	point->color = n_color;
}


void PAW_Point_show(const PAW_Point* const point, const uint32_t buffer)
{
	PAW_Write_To_Buffer(buffer, PAW_Vector_get_data(&point->position, 0), PAW_Vector_get_data(&point->position, 1),
			point->color);
}

void PAW_Point_drawOnTexture(const PAW_Point* const point, PAW_Texture* texture)
{
	*PAW_Texture_at(texture, PAW_Vector_get_data(&point->position, 0), PAW_Vector_get_data(&point->position, 1)) =
			point->color;
}

void PAW_Point_rotate(PAW_Point* const point, const PAW_Vector* const rotate_point,const int16_t degrees)
{
	PAW_Matrix rotation_matrix = {4};
	PAW_Matrix_to_rotation_matrix(&rotation_matrix, 0, 1, degrees);

	//position = rotation_matrix * (position - rotate_point) + rotate_point;
	PAW_Vector temp1 = PAW_Vector_sub(&point->position, rotate_point);
	PAW_Vector temp2 = PAW_Matrix_mul_vec(&rotation_matrix, &temp1);
	PAW_Vector temp3 = PAW_Vector_add(&temp2, rotate_point);
	PAW_Vector_assign(&point->position, &temp3);
}

void PAW_Point_translate(PAW_Point* const point, const PAW_Vector* const translation)
{
	PAW_Vector_add_assign(&point->position, translation);
}

void PAW_Point_rotate_helper(PAW_Point* const point, const PAW_Matrix* const rotation_matrix)
{
	*PAW_Vector_at(&point->position, 1) *= -1;
	*PAW_Vector_at(&point->position, 2) *= -1;
	//position = rotation_matrix * position;
	point->position = PAW_Matrix_mul_vec(&rotation_matrix, &point->position);
	*PAW_Vector_at(&point->position, 1) *= -1;
	*PAW_Vector_at(&point->position, 2) *= -1;
}
void PAW_Point_projection_helper(PAW_Point* const point, const PAW_Matrix* const projection_matrix)
{
	*PAW_Vector_at(&point->position, 1) *= -1;
	*PAW_Vector_at(&point->position, 2) *= -1;
	//position = projection_matrix * position
	point->position = PAW_Matrix_mul_vec(&projection_matrix, &point->position);
}

void PAW_Point_scale_helper(PAW_Point* const point, const float scale)
{
	PAW_Vector_mul_assign(&point->position, scale);
}
