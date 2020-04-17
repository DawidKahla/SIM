#include "PAW_Line.h"

void PAW_Line_change_color(PAW_Line* const line, const uint32_t n_color){

	line->color = n_color;

}


void PAW_Line_show(const PAW_Line* const line, const uint32_t buffer)
{
	const int32_t x1 = (int32_t) PAW_Vector_get_data(&line->begin, 0);
	const int32_t y1 = (int32_t) PAW_Vector_get_data(&line->begin, 1);
	const int32_t x2 = (int32_t) PAW_Vector_get_data(&line->end, 0);
	const int32_t y2 = (int32_t) PAW_Vector_get_data(&line->end, 1);

	//zmienne pomocnicze
	int32_t d, dx, dy, ai, bi, xi, yi;
	d = dx = dy = ai = bi = xi = yi = 0;

	int32_t xx = x1, yy = y1;

	//ustalanie kierunku rysowania
	if (x1 < x2)
	{
		xi = 1;
		dx = x2 - x1;
	}
	else
	{
		xi = -1;
		dx = x1 - x2;
	}

	if (y1 < y2)
	{
		yi = 1;
		dy = y2 - y1;
	}
	else
	{
		yi = -1;
		dy = y1 - y2;
	}

	//pierwszy piksel
	PAW_Write_To_Buffer(buffer, xx, yy, line->color);

	//oś wiodąca OX
	if (dx > dy)
	{
		ai = 2 * (dy - dx);
		bi = 2 * dy;
		d = bi - dx;

		//pętla po x
		while (xx != x2)
		{
			//test współczynnika
			if (d >= 0)
			{
				xx += xi;
				yy += yi;
				d += ai;
			}
			else
			{
				d += bi;
				xx += xi;
			}
			PAW_Write_To_Buffer(buffer, xx, yy, line->color);
		}
	}
	else
	{
		ai = 2 * (dx - dy);
		bi = 2 * dx;
		d = bi - dy;

		//pętla po y
		while (yy != y2)
		{
			//test współczynnika
			if (d >= 0)
			{
				xx += xi;
				yy += yi;
				d += ai;
			}
			else
			{
				d += bi;
				yy += yi;
			}
			PAW_Write_To_Buffer(buffer, xx, yy, line->color);
		}
	}
}

void PAW_Line_drawOnTexture(const PAW_Line* const line, PAW_Texture* texture)
{
	const int32_t x1 = (int32_t) PAW_Vector_get_data(&line->begin, 0);
	const int32_t y1 = (int32_t) PAW_Vector_get_data(&line->begin, 1);
	const int32_t x2 = (int32_t) PAW_Vector_get_data(&line->end, 0);
	const int32_t y2 = (int32_t) PAW_Vector_get_data(&line->end, 1);

	//zmienne pomocnicze
	int32_t d, dx, dy, ai, bi, xi, yi;
	d = dx = dy = ai = bi = xi = yi = 0;

	int32_t xx = x1, yy = y1;

	//ustalanie kierunku rysowania
	if (x1 < x2)
	{
		xi = 1;
		dx = x2 - x1;
	}
	else
	{
		xi = -1;
		dx = x1 - x2;
	}

	if (y1 < y2)
	{
		yi = 1;
		dy = y2 - y1;
	}
	else
	{
		yi = -1;
		dy = y1 - y2;
	}

	//pierwszy piksel
	*PAW_Texture_at(texture, xx, yy) = line->color;

	//oś wiodąca OX
	if (dx > dy)
	{
		ai = 2 * (dy - dx);
		bi = 2 * dy;
		d = bi - dx;

		//pętla po x
		while (xx != x2)
		{
			//test współczynnika
			if (d >= 0)
			{
				xx += xi;
				yy += yi;
				d += ai;
			}
			else
			{
				d += bi;
				xx += xi;
			}
			*PAW_Texture_at(texture, xx, yy) = line->color;
		}
	}
	else
	{
		ai = 2 * (dx - dy);
		bi = 2 * dx;
		d = bi - dy;

		//pętla po y
		while (yy != y2)
		{
			//test współczynnika
			if (d >= 0)
			{
				xx += xi;
				yy += yi;
				d += ai;
			}
			else
			{
				d += bi;
				yy += yi;
			}
			*PAW_Texture_at(texture, xx, yy) = line->color;
		}
	}
}

void PAW_Line_rotate(PAW_Line* const line, const PAW_Vector* const rotate_point, const int16_t degrees)
{
	PAW_Matrix rotation_matrix = {line->begin.size};
	PAW_Matrix_to_rotation_matrix(&rotation_matrix, 0, 1, degrees);

	//begin = rotation_matrix * (begin - rotate_point) + rotate_point;
	PAW_Vector temp1 = PAW_Vector_sub(&line->begin, rotate_point);
	PAW_Vector temp2 = PAW_Matrix_mul_vec(&rotation_matrix, &temp1);
	PAW_Vector temp3 = PAW_Vector_add(&temp2, rotate_point);
	PAW_Vector_assign(&line->begin, &temp3);

	//end = rotation_matrix * (end - rotate_point) + rotate_point;
	PAW_Vector temp4 = PAW_Vector_sub(&line->end, rotate_point);
	PAW_Vector temp5 = PAW_Matrix_mul_vec(&rotation_matrix, &temp4);
	PAW_Vector temp6 = PAW_Vector_add(&temp5, rotate_point);
	PAW_Vector_assign(&line->end, &temp6);
}

void PAW_Line_translate(PAW_Line* const line, const PAW_Vector* const translation)
{
	PAW_Vector_add_assign(&line->begin, translation);
	PAW_Vector_add_assign(&line->end, translation);
}

void PAW_Line_rotate_helper(PAW_Line* const line, const PAW_Matrix* const rotation_matrix)
{
	*PAW_Vector_at(&line->begin, 1) *= -1;
	*PAW_Vector_at(&line->begin, 2) *= -1;
	//begin = rotation_matrix * begin;
	line->begin = PAW_Matrix_mul_vec(rotation_matrix, &line->begin);
	*PAW_Vector_at(&line->begin, 1) *= -1;
	*PAW_Vector_at(&line->begin, 2) *= -1;

	*PAW_Vector_at(&line->end, 1) *= -1;
	*PAW_Vector_at(&line->end, 2) *= -1;
	//end = rotation_matrix * begin;
	line->end = PAW_Matrix_mul_vec(rotation_matrix, &line->end);
	*PAW_Vector_at(&line->end, 1) *= -1;
	*PAW_Vector_at(&line->end, 2) *= -1;
}
void PAW_Line_projection_helper(PAW_Line* const line, const PAW_Matrix* const projection_matrix)
{
	*PAW_Vector_at(&line->begin, 1) *= -1;
	*PAW_Vector_at(&line->begin, 2) *= -1;
	//begin = projection_matrix * begin;
	line->begin = PAW_Matrix_mul_vec(projection_matrix, &line->begin);

	*PAW_Vector_at(&line->end, 1) *= -1;
	*PAW_Vector_at(&line->end, 2) *= -1;
	//end = projection_matrix * begin;
	line->end = PAW_Matrix_mul_vec(projection_matrix, &line->end);
}

void PAW_Line_scale_helper(PAW_Line* const line, const float scale)
{
	PAW_Vector_mul_assign(&line->begin, scale);
	PAW_Vector_mul_assign(&line->end, scale);
}
