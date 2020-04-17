#include "PAW_3D_Projection.h"

PAW_Vector project_3D_to_2D(const PAW_Vector* const point_position)
{
		PAW_Vector result = {4};
		PAW_Matrix P = {4};
		P = projection_matrix(0.0f, 239.0f, 0.0f, 319.0f, 160.0f, 0.0f);
		PAW_Matrix diagonal = {4};
		PAW_Matrix_diagonal(&diagonal, 1.0f);
		PAW_Matrix Rx = diagonal;
		PAW_Matrix Ry = diagonal;
		PAW_Matrix Rz = diagonal;
		PAW_Matrix Rx2 = diagonal;

		PAW_Matrix_to_rotation_matrix(&Rx, 1, 2, 0 * 0.0f); //x rot
		PAW_Matrix_to_rotation_matrix(&Ry, 2, 0, 2 * 0.0f); //y rot
		PAW_Matrix_to_rotation_matrix(&Rz, 1, 0, 2 * 90.0f); //z rot
		PAW_Matrix_to_rotation_matrix(&Rx2, 1, 2, 2 * 0.0f); //x rot

		PAW_Vector point_position2 = *point_position;
		*PAW_Vector_at(&point_position2, 1) *= -1;
		*PAW_Vector_at(&point_position2, 2) *= -1;
		//result = Rz * point_position2;
		result = PAW_Matrix_mul_vec(&Rz, &point_position2);
		*PAW_Vector_at(&point_position2, 1) *= -1;
		*PAW_Vector_at(&point_position2, 2) *= -1;
		*PAW_Vector_at(&point_position2, 1) *= -1;
		*PAW_Vector_at(&point_position2, 2) *= -1;
		//result = P * result;
		result = PAW_Matrix_mul_vec(&P, &result);

		PAW_Vector temp3 = {4, {540.0f, 290.0f, 0.0f, 0.0f}};

		PAW_Vector_add_assign(&result, &temp3);

		PAW_Vector_div_assign(&result, 2);
		PAW_Vector_print(stdout, &result);

		return result;

}

PAW_Matrix projection_matrix(const float left, const float right, const float top, const float bottom, const float near, const float far)
{

	PAW_Matrix projection_matrix = {4};
	PAW_Matrix_set_data(&projection_matrix, 0, 0, 2 * near / (right - left));
	PAW_Matrix_set_data(&projection_matrix, 0, 2, (right + left) / (right - left));
	PAW_Matrix_set_data(&projection_matrix, 1, 1, 2 * near / (top - bottom));
	PAW_Matrix_set_data(&projection_matrix, 1, 2, (top + bottom) / (top - bottom));
	PAW_Matrix_set_data(&projection_matrix, 2, 2, -(far + near) / (far - near));
	PAW_Matrix_set_data(&projection_matrix, 2, 3, -2 * far * near / (far - near));
	return projection_matrix;
}
