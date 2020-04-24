#include "PAW_Figure.h"

const float left = -120.0f;
const float right = 120.0f;
const float top = 120.0f;
const float bottom = -120.0f;
const float near = 120.0f;
const float far = -120.0f;

int compareSquareDistance(const void* square01, const void* square02)
{
	
	PAW_Square* square1 = (PAW_Square*)square01;
	int distance1 =
		square1->corner.data[2] + square1->side[0].data[2] / 2 + square1->side[1].data[2] / 2;
	PAW_Square* square2 = (PAW_Square*)square02;
	int distance2 =
		square2->corner.data[2] + square2->side[0].data[2] / 2 + square2->side[1].data[2] / 2;
	if (distance1 < distance2) return 1;
	else if (distance1 == distance2) return 0;
	else return -1;
}

PAW_Figure PAW_Figure_create(const uint16_t circles, const uint16_t points, const uint16_t lines, const uint16_t squares){
	PAW_Figure figure;
	figure.size = circles + points + lines;
	figure.circles = (PAW_Circle*) malloc( circles * sizeof(PAW_Circle));
	figure.points = (PAW_Point*) malloc( points * sizeof(PAW_Point));
	figure.lines = (PAW_Line*) malloc( lines * sizeof(PAW_Line));
	figure.squares = (PAW_Square*) malloc( squares * sizeof(PAW_Square));
	figure.flag=0;
	for(int i = 0;i<4;i++)
		figure.elements[i] = 0;

	return figure;
}

void PAW_Figure_destr(PAW_Figure* figure)
{
	if(figure->elements[0])
		free(figure->circles);
	if(figure->elements[1])
		free(figure->points);
	if(figure->elements[2])
		free(figure->lines);
	if(figure->elements[3])
		free(figure->squares);
}


void PAW_Figure_push_circle(PAW_Figure* const figure, PAW_Circle const n_circle){
	figure->circles[figure->elements[0]] = n_circle;
	figure->elements[0]++;
}

void PAW_Figure_push_point(PAW_Figure* const figure, PAW_Point const n_points){
	figure->points[figure->elements[1]] = n_points;
	figure->elements[1]++;
}

void PAW_Figure_push_line(PAW_Figure* const figure, PAW_Line const n_line){
	figure->lines[figure->elements[2]] = n_line;
	figure->elements[2]++;
}

void PAW_Figure_push_square(PAW_Figure* const figure, PAW_Square const n_square){
	figure->squares[figure->elements[3]] = n_square;
	figure->elements[3]++;
}

void PAW_Figure_show(const PAW_Figure* const figure, const uint32_t buffer)
{
	for (size_t i = 0; i <figure->elements[0]; ++i)
	{
		PAW_Circle_show(&figure->circles[i], buffer);
	}

	for (size_t i = 0; i <figure->elements[1]; ++i)
	{
		PAW_Point_show(&figure->points[i], buffer);
	}

	for (size_t i = 0; i <figure->elements[2]; ++i)
	{
		PAW_Line_show(&figure->lines[i], buffer);
	}
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Square_show(&figure->squares[i], buffer);
	}
}

void PAW_Figure_translate(PAW_Figure* const figure, const PAW_Vector* const n_translation)
{
	for (size_t i = 0; i <figure->elements[0]; ++i)
	{
		PAW_Circle_translate(&figure->circles[i], n_translation);
	}

	for (size_t i = 0; i <figure->elements[1]; ++i)
	{
		PAW_Point_translate(&figure->points[i], n_translation);
	}

	for (size_t i = 0; i <figure->elements[2]; ++i)
	{
		PAW_Line_translate(&figure->lines[i], n_translation);
	}
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Square_translate(&figure->squares[i], n_translation);
	}
}

void PAW_Figure_rotate(PAW_Figure* const figure, const PAW_Vector* const rotate_point, const int16_t degrees)
{
	for (size_t i = 0; i <figure->elements[0]; ++i)
	{
		PAW_Circle_rotate(&figure->circles[i], rotate_point, degrees);
	}

	for (size_t i = 0; i <figure->elements[1]; ++i)
	{
		PAW_Point_rotate(&figure->points[i], rotate_point, degrees);
	}

	for (size_t i = 0; i <figure->elements[2]; ++i)
	{
		PAW_Line_rotate(&figure->lines[i], rotate_point, degrees);
	}
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Square_rotate(&figure->squares[i], rotate_point, degrees);
	}

}



void PAW_Figure_project3D_to_2D(PAW_Figure* const figure)
{
	PAW_Matrix P = projection_matrix(left, right, top, bottom, near, far);
	for (size_t i = 0; i <figure->elements[0]; ++i)
	{
		PAW_Circle_projection_helper(&figure->circles[i], &P);
	}
	for (size_t i = 0; i <figure->elements[1]; ++i)
	{
		PAW_Point_projection_helper(&figure->points[i], &P);
	}
	for (size_t i = 0; i <figure->elements[2]; ++i)
	{
		PAW_Line_projection_helper(&figure->lines[i], &P);
	}

	qsort(figure->squares, figure->elements[3], sizeof(PAW_Square), &compareSquareDistance);
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Square_projection_helper(&figure->squares[i], &P);
	}
}

void PAW_Figure_copy(PAW_Figure* from, PAW_Figure* to)
{
	*to = PAW_Figure_create(from->elements[0], from->elements[1], from->elements[2], from->elements[3]);
	for (size_t i = 0; i <from->elements[0]; ++i)
		{
			PAW_Figure_push_circle(to, from->circles[i]);
		}

		for (size_t i = 0; i <from->elements[1]; ++i)
		{
			PAW_Figure_push_point(to, from->points[i]);
		}

		for (size_t i = 0; i <from->elements[2]; ++i)
		{
			PAW_Figure_push_line(to, from->lines[i]);
		}
		for (size_t i = 0; i <from->elements[3]; ++i)
		{
			PAW_Figure_push_square(to, from->squares[i]);
		}
}

PAW_Figure PAW_Figure_project3D_to_2D_new(PAW_Figure* const figure)
{
	PAW_Figure figure2d;
	PAW_Figure_copy(figure, &figure2d);
	PAW_Matrix P = projection_matrix(left, right, top, bottom, near, far);
	for (size_t i = 0; i <figure2d.elements[0]; ++i)
	{
		PAW_Circle_projection_helper(&figure2d.circles[i], &P);
	}
	for (size_t i = 0; i <figure2d.elements[1]; ++i)
	{
		PAW_Point_projection_helper(&figure2d.points[i], &P);
	}
	for (size_t i = 0; i <figure2d.elements[2]; ++i)
	{
		PAW_Line_projection_helper(&figure2d.lines[i], &P);
	}

	qsort(figure2d.squares, figure2d.elements[3], sizeof(PAW_Square), &compareSquareDistance);
	for (size_t i = 0; i <figure2d.elements[3]; ++i)
	{
		PAW_Square_projection_helper(&figure2d.squares[i], &P);
	}
	return figure2d;
}

void PAW_Figure_rotate3D(PAW_Figure* const figure, const float x_degrees, const float y_degrees, const float z_degrees)
{
	PAW_Matrix Rx = {4};
	PAW_Matrix Ry = {4};
	PAW_Matrix Rz = {4};
	PAW_Matrix R = {4};
	PAW_Matrix_to_rotation_matrix(&Rx, 1, 2, x_degrees);
	PAW_Matrix_to_rotation_matrix(&Ry, 2, 0, y_degrees);
	PAW_Matrix_to_rotation_matrix(&Rz, 1, 0, z_degrees);

	//R = Rz * Ry * Rx;
	PAW_Matrix temp1 = PAW_Matrix_mul_mat(&Rz, &Ry);
	PAW_Matrix temp2 = PAW_Matrix_mul_mat(&temp1, &Rx);
	R = temp2;
	for (size_t i = 0; i <figure->elements[0]; ++i)
	{
		PAW_Circle_rotate_helper(&figure->circles[i], &R);
	}
	for (size_t i = 0; i <figure->elements[1]; ++i)
	{
		PAW_Point_rotate_helper(&figure->points[i], &R);
	}
	for (size_t i = 0; i <figure->elements[2]; ++i)
	{
		PAW_Line_rotate_helper(&figure->lines[i], &R);
	}
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Square_rotate_helper(&figure->squares[i], &R);
	}
}

void PAW_Figure_scale3D(PAW_Figure* const figure, const float scale)
{
	for (size_t i = 0; i <figure->elements[0]; ++i)
	{
		PAW_Circle_scale_helper(&figure->circles[i], scale);
	}
	for (size_t i = 0; i <figure->elements[1]; ++i)
	{
		PAW_Point_scale_helper(&figure->points[i], scale);
	}
	for (size_t i = 0; i <figure->elements[2]; ++i)
	{
		PAW_Line_scale_helper(&figure->lines[i], scale);
	}
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Square_scale_helper(&figure->squares[i], scale);
	}
}


void PAW_Figure_toPyramid(PAW_Figure* const figure, const float a_length, const uint32_t a_color)
{
	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}

	const float length = 0.5f * a_length;
	PAW_Vector P1 = {4, {-length, -length, -length, 1.0f}};
	PAW_Vector P2 = {4, {-length,-length, length, 1.0f}};
	PAW_Vector P3 = {4, {length, -length, -length, 1.0f}};
	PAW_Vector P4 = {4, {length, -length, length, 1.0f}};
	PAW_Vector P5 = {4, {0, length, 0, 1.0f}};

	PAW_Vector S1 = {4, {-50.0f,-20.0f,-10.0f,1.0f}};
	PAW_Vector S2 = {4, {20.0f,10.0f,50.0f,1.0f}};
	PAW_Vector S3 = {4, {0,0,0,1.0f}};

	PAW_Line SL1 = {a_color, false, S3, S1};
	PAW_Line SL2 = {a_color, false, S2, S1};

	PAW_Line L1 = {a_color, false, P1, P2};
	PAW_Line L2 = {a_color, false, P2, P4};
	PAW_Line L3 = {a_color, false, P4, P3};
	PAW_Line L4(P3, P1, a_color);

	PAW_Line L5 = {a_color, false, P5, P1};
	PAW_Line L6 = {a_color, false, P5, P2};
	PAW_Line L7 = {a_color, false, P5, P3};
	PAW_Line L8 = {a_color, false, P5, P4};

	uint8_t red [4] = {255,232,23,23};
	uint8_t blue [4] = {255,23,127,232};

	PAW_figure_paint(figure, &L7, &L8, red);


	PAW_figure_push_line(figure, L1);
	PAW_figure_push_line(figure, L2);
	PAW_figure_push_line(figure, L3);
	PAW_figure_push_line(figure, L4);

	PAW_figure_push_line(figure, L5);
	PAW_figure_push_line(figure, L6);
	PAW_figure_push_line(figure, L7);
	PAW_figure_push_line(figure, L8);
}

void PAW_Figure_toCross(PAW_Figure* const figure, const float a_length, const uint32_t a_color)
{
	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}

	const float length = 0.5f * a_length;

	PAW_Vector P1 = {4, {-0.5f*length, -length, -0.5f*length, 1.0f}};
	PAW_Vector P2 = {4, {-0.5f*length,-length, 0.5f*length, 1.0f}};
	PAW_Vector P3 = {4, {0.5f*length, -length, -0.5f*length, 1.0f}};
	PAW_Vector P4 = {4, {0.5f*length, -length, 0.5f*length, 1.0f}};

	PAW_Vector P5 = {4, {-0.5f*length, -0.5f*length, -0.5f*length, 1.0f}};
	PAW_Vector P6 = {4, {-0.5f*length,-0.5f*length, 0.5f*length, 1.0f}};
	PAW_Vector P7 = {4, {0.5f*length, -0.5f*length, -0.5f*length, 1.0f}};
	PAW_Vector P8 = {4, {0.5f*length, -0.5f*length, 0.5f*length, 1.0f}};

	PAW_Vector P9 = {4, {-length, -0.5f*length, 0.5f*length, 1.0f}};
	PAW_Vector P10 = {4, {length, -0.5f*length, 0.5f*length, 1.0f}};

	PAW_Vector P11 = {4, {-length, 0, 0.5f*length, 1.0f}};
	PAW_Vector P12 = {4, {length, 0, 0.5f*length, 1.0f}};

	PAW_Vector P14 = {4, {-length, -0.5f*length, -0.5f*length, 1.0f}};
	PAW_Vector P13 = {4, {length, -0.5f*length, -0.5f*length, 1.0f}};

	PAW_Vector P15 = {4, {-length, 0, -0.5f*length, 1.0f}};
	PAW_Vector P16 = {4, {length, 0, -0.5f*length, 1.0f}};

	PAW_Vector P17 = {4, {-0.5f*length, 0.0f*length, -0.5f*length, 1.0f}};
	PAW_Vector P18 = {4, {0.5f*length, 0.0f*length, -0.5f*length, 1.0f}};

	PAW_Vector P19 = {4, {-0.5f*length,-0.0f*length, 0.5f*length, 1.0f}};
	PAW_Vector P20 = {4, {0.5f*length, -0.0f*length, 0.5f*length, 1.0f}};

	PAW_Vector P23 = {4, {-0.5f*length, 0.5f*length, -0.5f*length, 1.0f}};
	PAW_Vector P24 = {4, {0.5f*length, 0.5f*length, -0.5f*length, 1.0f}};

	PAW_Vector P21 = {4, {-0.5f*length,0.5f*length, 0.5f*length, 1.0f}};
	PAW_Vector P22 = {4, {0.5f*length, 0.5f*length, 0.5f*length, 1.0f}};

	PAW_Line L1 = {a_color, false, P1, P3};
	PAW_Line L2 = {a_color, false, P2, P4};
	PAW_Line L3 = {a_color, false, P3, P4};
	PAW_Line L4 = {a_color, false, P2, P1};
	PAW_Line L5 = {a_color, false, P1, P5};
	PAW_Line L6 = {a_color, false, P2, P6};
	PAW_Line L7 = {a_color, false, P3, P7};
	PAW_Line L8 = {a_color, false, P4, P8};
	PAW_Line L9 = {a_color, false, P6, P9};
	PAW_Line L10 = {a_color, false, P8, P10};
	PAW_Line L11 = {a_color, false, P11, P9};
	PAW_Line L12 = {a_color, false, P12, P10};
	PAW_Line L13 = {a_color, false, P14, P5};
	PAW_Line L14 = {a_color, false, P13, P7};
	PAW_Line L15 = {a_color, false, P14, P15};
	PAW_Line L16 = {a_color, false, P13, P16};
	PAW_Line L17 = {a_color, false, P15, P11};
	PAW_Line L18 = {a_color, false, P16, P12};
	PAW_Line L19 = {a_color, false, P9, P14};
	PAW_Line L20 = {a_color, false, P13, P10};
	PAW_Line L21 = {a_color, false, P15, P17};
	PAW_Line L22 = {a_color, false, P16, P18};
	PAW_Line L23 = {a_color, false, P11, P19};
	PAW_Line L24 = {a_color, false, P12, P20};
	PAW_Line L25 = {a_color, false, P17, P23};
	PAW_Line L26 = {a_color, false, P18, P24};
	PAW_Line L27 = {a_color, false, P19, P21};
	PAW_Line L28 = {a_color, false, P22, P20};
	PAW_Line L29 = {a_color, false, P23, P21};
	PAW_Line L30 = {a_color, false, P24, P22};
	PAW_Line L31 = {a_color, false, P22, P21};
	PAW_Line L32 = {a_color, false, P23, P24};

	PAW_Figure_push_line(figure, L1);
	PAW_Figure_push_line(figure, L2);
	PAW_Figure_push_line(figure, L3);
	PAW_Figure_push_line(figure, L4);
	PAW_Figure_push_line(figure, L5);
	PAW_Figure_push_line(figure, L6);
	PAW_Figure_push_line(figure, L7);
	PAW_Figure_push_line(figure, L8);
	PAW_Figure_push_line(figure, L9);
	PAW_Figure_push_line(figure, L10);
	PAW_Figure_push_line(figure, L11);
	PAW_Figure_push_line(figure, L12);
	PAW_Figure_push_line(figure, L13);
	PAW_Figure_push_line(figure, L14);
	PAW_Figure_push_line(figure, L15);
	PAW_Figure_push_line(figure, L16);
	PAW_Figure_push_line(figure, L17);
	PAW_Figure_push_line(figure, L18);
	PAW_Figure_push_line(figure, L19);
	PAW_Figure_push_line(figure, L20);
	PAW_Figure_push_line(figure, L21);
	PAW_Figure_push_line(figure, L22);
	PAW_Figure_push_line(figure, L23);
	PAW_Figure_push_line(figure, L24);
	PAW_Figure_push_line(figure, L25);
	PAW_Figure_push_line(figure, L26);
	PAW_Figure_push_line(figure, L27);
	PAW_Figure_push_line(figure, L28);
	PAW_Figure_push_line(figure, L29);
	PAW_Figure_push_line(figure, L30);
	PAW_Figure_push_line(figure, L31);
	PAW_Figure_push_line(figure, L32);
}


void PAW_Figure_toCube(PAW_Figure* const figure, const float a_length, const uint32_t a_color)
{
	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}

	const float length = 0.5f * a_length;

	PAW_Vector P1 = {4, {-length, -length, length, 1.0f}};
	PAW_Vector P2 = {4, {length, -length, length, 1.0f}};
	PAW_Vector P3 = {4, {-length, length, length, 1.0f}};
	PAW_Vector P4 = {4, {length, length, length, 1.0f}};
	PAW_Vector P5 = {4, {-length, -length, -length, 1.0f}};
	PAW_Vector P6 = {4, {length, -length, -length, 1.0f}};
	PAW_Vector P7 = {4, {-length, length, -length, 1.0f}};
	PAW_Vector P8 = {4, {length, length, -length, 1.0f}};


	PAW_Line L1 = {a_color, false, P1, P2};
	PAW_Line L2 = {a_color, false, P2, P4};
	PAW_Line L3 = {a_color, false, P3, P4};
	PAW_Line L4 = {a_color, false, P3, P1};
	PAW_Line L5 = {a_color, false, P1, P5};
	PAW_Line L6 = {a_color, false, P5, P7};
	PAW_Line L7 = {a_color, false, P7, P3};
	PAW_Line L8 = {a_color, false, P7, P8};
	PAW_Line L9 = {a_color, false, P5, P6};
	PAW_Line L10 = {a_color, false, P6, P8};
	PAW_Line L11 = {a_color, false, P8, P4};
	PAW_Line L12 = {a_color, false, P6, P2};

	uint8_t green[] = {255,85,255,51};
	uint8_t purple[] = {255,200,43,199};

	PAW_Figure_paint(figure, &L1, &L3, *(uint32_t*)green);
	PAW_Figure_paint(figure, &L10, &L6, *(uint32_t*)purple);

	PAW_Figure_push_line(figure, L1);
	PAW_Figure_push_line(figure, L2);
	PAW_Figure_push_line(figure, L3);
	PAW_Figure_push_line(figure, L4);
	PAW_Figure_push_line(figure, L5);
	PAW_Figure_push_line(figure, L6);
	PAW_Figure_push_line(figure, L7);
	PAW_Figure_push_line(figure, L8);
	PAW_Figure_push_line(figure, L9);
	PAW_Figure_push_line(figure, L10);
	PAW_Figure_push_line(figure, L11);
	PAW_Figure_push_line(figure, L12);
}



void PAW_Figure_toExperimental(PAW_Figure* const figure, const float a_length, const uint32_t a_color)
{
	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}

	const float length = 0.5f * a_length;

	PAW_Vector P1 = {4, {-length, -length, length, 1.0f}};
	PAW_Vector P2 = {4, {length, -length, length, 1.0f}};
	PAW_Vector P3 = {4, {-length, length, length, 1.0f}};
	PAW_Vector P4 = {4, {length, length, length, 1.0f}};
	PAW_Vector P5 = {4, {-length, -length, -length, 1.0f}};
	PAW_Vector P6 = {4, {length, -length, -length, 1.0f}};
	PAW_Vector P7 = {4, {-length, length, -length, 1.0f}};
	PAW_Vector P8 = {4, {length, length, -length, 1.0f}};


	PAW_Line L1 = {a_color, false, P1, P2};
	PAW_Line L2 = {a_color, false, P2, P4};
	PAW_Line L3 = {a_color, false, P3, P4};
	PAW_Line L4 = {a_color, false, P3, P1};
	PAW_Line L5 = {a_color, false, P1, P5};
	PAW_Line L6 = {a_color, false, P5, P7};
	PAW_Line L7 = {a_color, false, P7, P3};
	PAW_Line L8 = {a_color, false, P7, P8};
	PAW_Line L9 = {a_color, false, P5, P6};
	PAW_Line L10 = {a_color, false, P6, P8};
	PAW_Line L11 = {a_color, false, P8, P4};
	PAW_Line L12 = {a_color, false, P6, P2};

	uint8_t green[] = {255,85,255,51};
	uint8_t purple[] = {255,200,43,199};
	uint8_t yellow[] = {255,199,255,0};

	PAW_Figure_paint(figure, &L1, &L3, *(uint32_t*)green);
	PAW_Figure_paint(figure, &L10, &L6, *(uint32_t*)purple);
	PAW_Figure_paint(figure, &L11, &L12, *(uint32_t*)yellow);

	PAW_Figure_push_line(figure, L1);
	PAW_Figure_push_line(figure, L2);
	PAW_Figure_push_line(figure, L3);
	PAW_Figure_push_line(figure, L4);
	PAW_Figure_push_line(figure, L5);
	PAW_Figure_push_line(figure, L6);
	PAW_Figure_push_line(figure, L7);
	PAW_Figure_push_line(figure, L8);
	PAW_Figure_push_line(figure, L9);
	PAW_Figure_push_line(figure, L10);
	PAW_Figure_push_line(figure, L11);
	PAW_Figure_push_line(figure, L12);
}

void PAW_Figure_paint(PAW_Figure* const figure, const PAW_Line* const line1, const PAW_Line* const line2, uint32_t clr)
{

	PAW_Vector* vec_ptr1 = NULL;
	PAW_Vector* vec_ptr2 = NULL;

	// d to beda roznice, delty itd.
	float dx1, dx2, dy1, dy2, dz1, dz2;
	// c to kursory albo iteratory
	float cx1, cy1, cz1, cx2, cy2, cz2;

	//m to milestone'y, punkty zaczepne dla linii tworzacych sciane
	float mx1,mx2,my1,my2,mz1,mz2;

	// pomocnicze
	int loopint = 0;

	cx1 = PAW_Vector_get_data(&line1->begin, 0);
	cy1 = PAW_Vector_get_data(&line1->begin, 1);
	cz1 = PAW_Vector_get_data(&line1->begin, 2);

	cx2 = PAW_Vector_get_data(&line2->begin, 0);
	cy2 = PAW_Vector_get_data(&line2->begin, 1);
	cz2 = PAW_Vector_get_data(&line2->begin, 2);


	//DISTANCES ON LINE 1
	 dx1 = PAW_Vector_get_data(&line1->end, 0) - PAW_Vector_get_data(&line1->begin, 0);
	 dy1 = PAW_Vector_get_data(&line1->end, 1) - PAW_Vector_get_data(&line1->begin, 1);
	 dz1 = PAW_Vector_get_data(&line1->end, 2) - PAW_Vector_get_data(&line1->begin, 2);


	//DISTANCES ON LINE 2
	 dx2 = PAW_Vector_get_data(&line2->end, 0) - PAW_Vector_get_data(&line2->begin, 0);
	 dy2 = PAW_Vector_get_data(&line2->end, 1) - PAW_Vector_get_data(&line2->begin, 1);
	 dz2 = PAW_Vector_get_data(&line2->end, 2) - PAW_Vector_get_data(&line2->begin, 2);

	// dlugosci wektorow
	float length1 = sqrt(dx1*dx1 + dy1*dy1 + dz1*dz1);
	float length2 = sqrt(dx2*dx2 + dy2*dy2 + dz2*dz2);

	int density = 2; // jak gesta sciana? 2 oznacza linie co 0.5f

	loopint = (int)length1;

	 // MILESTONE'Y DLA KAZDEGO KURSORA
	 mx1 = dx1/(density*loopint);
	 my1 = dy1/(density*loopint);
	 mz1 = dz1/(density*loopint);
	 mx2 = dx2/(density*loopint);
	 my2 = dy2/(density*loopint);
	 mz2 = dz2/(density*loopint);


	 // jesli rozne dlugosci - nic sie nie dzieje
	if ((length1 == length2)&&(length1 != 0.0f)) {
		for(int i = 0; i < density*loopint; ++i) {

			PAW_Vector vec1 = {4, {cx1,cy1,cz1,1.0f}};
			PAW_Vector vec2 = {4, {cx2,cy2,cz2,1.0f}};

			PAW_Line line = {clr, false, vec1, vec2};
			PAW_Figure_push_line(figure, line);

			//przesuniecie kursorow
			cx1 += mx1;
			cy1 += my1;
			cz1 += mz1;
			cx2 += mx2;
			cy2 += my2;
			cz2 += mz2;
		}
	}
}

void PAW_Figure_toTexturedCube(PAW_Figure* const figure, const float a_length, const uint32_t a_color)
{
	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}
	PAW_Texture texture = {0, 0, 0, 0};

	PAW_Texture_prepare(&texture, a_length, a_length, 0xFF177FE9);

	for(int i = 0; i < a_length / 2; ++i)
		for(int j = 0; j < a_length / 2; ++j)
		{
			PAW_Vector pointVec = {4, { i + a_length / 4, j + a_length / 4, 0, 0}};
			PAW_Point point = {pointVec, 1, 0xFFE8A017};
			PAW_Point_drawOnTexture(&point, &texture);
		}

	PAW_Vector line1_start = {4, {a_length / 4, a_length / 4, 0, 0}};
	PAW_Vector line1_end = {4, {3 * a_length / 4, 3 * a_length / 4, 0, 0}};
	PAW_Line line1 = {0xFFFFFFFF, 1, line1_start, line1_end};
	PAW_Line_drawOnTexture(&line1, &texture);

	PAW_Vector line2_start = {4, {3 * a_length / 4, a_length / 4, 0, 0}};
	PAW_Vector line2_end = {4, {a_length / 4, 3 * a_length / 4, 0, 0}};
	PAW_Line line2 = {0xFFFFFFFF, 1, line2_start, line2_end};
	PAW_Line_drawOnTexture(&line2, &texture);

	PAW_Vector circle1Center = { 4,{ a_length / 2, a_length / 2, 0, 0}};
	PAW_Circle circle1 = {0xFF55FF33, 0, a_length / 4, circle1Center};
	PAW_Circle_drawOnTexture(&circle1, &texture);

	PAW_Vector circle2Center = { 4,{ a_length / 2, a_length / 2, 0, 0}};
	PAW_Circle circle2 = {0xFF55FF33, 1, a_length / 8, circle2Center};
	PAW_Circle_drawOnTexture(&circle2, &texture);

	PAW_Vector corner1 = {4, {0, 0, 0, 1.0}};
	PAW_Vector side1 = {4, {a_length, 0, 0, 0}};
	PAW_Vector side2 = {4, {0, a_length, 0, 0}};
	PAW_Vector side3 = {4, {0, 0, a_length, 0}};
	PAW_Square square = {corner1, {side1, side2}, 1, texture};
	PAW_Figure_push_square(figure, square);
	PAW_Square square2 = {corner1, {side1, side3}, 0};
	PAW_Figure_push_square(figure, square2);
	PAW_Square square3 = {corner1, {side2, side3}, 0};
	PAW_Figure_push_square(figure, square3);

	PAW_Vector corner2 = {4, {a_length, a_length, a_length, 1.0}};
	PAW_Vector side4 = {4, {-a_length, 0, 0, 0}};
	PAW_Vector side5 = {4, {0, -a_length, 0, 0}};
	PAW_Vector side6 = {4, {0, 0, -a_length, 0}};
	PAW_Square square4 = {corner2, {side4, side5}, 0};
	PAW_Figure_push_square(figure, square4);
	PAW_Square square5 = {corner2, {side4, side6}, 0};
	PAW_Figure_push_square(figure, square5);
	PAW_Square square6 = {corner2, {side5, side6}, 0};
	PAW_Figure_push_square(figure, square6);
}

void PAW_Figure_toDice(PAW_Figure* const figure, const float a_length, const uint32_t a_color)
{
	const uint32_t green = 0xFF55FF33;//{255,85,255,51};
	const uint32_t black = 0xFF000000;//{255,0,0,0};
	const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
	const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
	const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
	const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};

	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}
	PAW_Texture texture1 = {0, 0, 0, 0};
	PAW_Texture_prepare(&texture1, a_length, a_length, black);
	PAW_Vector circle1Center = { 4,{ a_length / 2, a_length / 2, 0, 0}};
	PAW_Circle circle1 = {white, 1, a_length / 4, circle1Center};
	PAW_Circle_drawOnTexture(&circle1, &texture1);

	PAW_Texture texture2 = {0, 0, 0, 0};
	PAW_Texture_prepare(&texture2, a_length, a_length, red);
	PAW_Vector circle21Center = { 4,{ a_length / 3, a_length / 3, 0, 0}};
	PAW_Circle circle21 = {blue, 1, a_length / 8, circle21Center};
	PAW_Circle_drawOnTexture(&circle21, &texture2);
	PAW_Vector circle22Center = { 4,{2 * a_length / 3, 2 * a_length / 3, 0, 0}};
	PAW_Circle circle22 = {blue, 1, a_length / 8, circle22Center};
	PAW_Circle_drawOnTexture(&circle22, &texture2);

	PAW_Texture texture3 = {0, 0, 0, 0};
	PAW_Texture_prepare(&texture3, a_length, a_length, yellow);
	PAW_Vector circle31Center = { 4,{ a_length / 6, a_length / 6, 0, 0}};
	PAW_Circle circle31 = {green, 1, a_length / 8, circle31Center};
	PAW_Circle_drawOnTexture(&circle31, &texture3);
	PAW_Vector circle32Center = { 4,{a_length / 2, a_length / 2, 0, 0}};
	PAW_Circle circle32 = {green, 1, a_length / 8, circle32Center};
	PAW_Circle_drawOnTexture(&circle32, &texture3);
	PAW_Vector circle33Center = { 4,{5 * a_length / 6, 5 * a_length / 6, 0, 0}};
	PAW_Circle circle33 = {green, 1, a_length / 8, circle33Center};
	PAW_Circle_drawOnTexture(&circle33, &texture3);

	PAW_Texture texture4 = {0, 0, 0, 0};
	PAW_Texture_prepare(&texture4, a_length, a_length, green);
	PAW_Vector circle41Center = { 4,{ a_length / 3, a_length / 3, 0, 0}};
	PAW_Circle circle41 = {yellow, 1, a_length / 8, circle41Center};
	PAW_Circle_drawOnTexture(&circle41, &texture4);
	PAW_Vector circle42Center = { 4,{2 * a_length / 3, 2 * a_length / 3, 0, 0}};
	PAW_Circle circle42 = {yellow, 1, a_length / 8, circle42Center};
	PAW_Circle_drawOnTexture(&circle42, &texture4);
	PAW_Vector circle43Center = { 4,{ a_length / 3, 2 * a_length / 3, 0, 0}};
	PAW_Circle circle43 = {yellow, 1, a_length / 8, circle43Center};
	PAW_Circle_drawOnTexture(&circle43, &texture4);
	PAW_Vector circle44Center = { 4,{2 * a_length / 3, a_length / 3, 0, 0}};
	PAW_Circle circle44 = {yellow, 1, a_length / 8, circle44Center};
	PAW_Circle_drawOnTexture(&circle44, &texture4);

	PAW_Texture texture5 = {0, 0, 0, 0};
	PAW_Texture_prepare(&texture5, a_length, a_length, blue);
	PAW_Vector circle51Center = { 4,{ a_length / 6, a_length / 6, 0, 0}};
	PAW_Circle circle51 = {red, 1, a_length / 8, circle51Center};
	PAW_Circle_drawOnTexture(&circle51, &texture5);
	PAW_Vector circle52Center = { 4,{a_length / 2, a_length / 2, 0, 0}};
	PAW_Circle circle52 = {red, 1, a_length / 8, circle52Center};
	PAW_Circle_drawOnTexture(&circle52, &texture5);
	PAW_Vector circle53Center = { 4,{5 * a_length / 6, 5 * a_length / 6, 0, 0}};
	PAW_Circle circle53 = {red, 1, a_length / 8, circle53Center};
	PAW_Circle_drawOnTexture(&circle53, &texture5);
	PAW_Vector circle54Center = { 4,{ a_length / 6, 5 * a_length / 6, 0, 0}};
	PAW_Circle circle54 = {red, 1, a_length / 8, circle54Center};
	PAW_Circle_drawOnTexture(&circle54, &texture5);
	PAW_Vector circle55Center = { 4,{ 5 * a_length / 6, a_length / 6, 0, 0}};
	PAW_Circle circle55 = {red, 1, a_length / 8, circle55Center};
	PAW_Circle_drawOnTexture(&circle55, &texture5);

	PAW_Texture texture6 = {0, 0, 0, 0};
	PAW_Texture_prepare(&texture6, a_length, a_length, white);
	PAW_Vector circle61Center = { 4,{ a_length / 3, a_length / 5, 0, 0}};
	PAW_Circle circle61 = {black, 1, a_length / 8, circle61Center};
	PAW_Circle_drawOnTexture(&circle61, &texture6);
	PAW_Vector circle62Center = { 4,{ a_length / 3, a_length / 2, 0, 0}};
	PAW_Circle circle62 = {black, 1, a_length / 8, circle62Center};
	PAW_Circle_drawOnTexture(&circle62, &texture6);
	PAW_Vector circle63Center = { 4,{ a_length / 3, 4 * a_length / 5, 0, 0}};
	PAW_Circle circle63 = {black, 1, a_length / 8, circle63Center};
	PAW_Circle_drawOnTexture(&circle63, &texture6);
	PAW_Vector circle64Center = { 4,{ 2 * a_length / 3, a_length / 5, 0, 0}};
	PAW_Circle circle64 = {black, 1, a_length / 8, circle64Center};
	PAW_Circle_drawOnTexture(&circle64, &texture6);
	PAW_Vector circle65Center = { 4,{ 2 * a_length / 3, a_length / 2, 0, 0}};
	PAW_Circle circle65 = {black, 1, a_length / 8, circle65Center};
	PAW_Circle_drawOnTexture(&circle65, &texture6);
	PAW_Vector circle66Center = { 4,{ 2 * a_length / 3, 4 * a_length / 5, 0, 0}};
	PAW_Circle circle66 = {black, 1, a_length / 8, circle66Center};
	PAW_Circle_drawOnTexture(&circle66, &texture6);

	PAW_Vector corner1 = {4, {0, 0, 0, 1.0}};
	PAW_Vector side1 = {4, {a_length, 0, 0, 0}};
	PAW_Vector side2 = {4, {0, a_length, 0, 0}};
	PAW_Vector side3 = {4, {0, 0, a_length, 0}};
	PAW_Square square = {corner1, {side1, side2}, 1, texture1};
	PAW_Figure_push_square(figure, square);
	PAW_Square square2 = {corner1, {side1, side3}, 1, texture2};
	PAW_Figure_push_square(figure, square2);
	PAW_Square square3 = {corner1, {side2, side3}, 1, texture3};
	PAW_Figure_push_square(figure, square3);

	PAW_Vector corner2 = {4, {a_length, a_length, a_length, 1.0}};
	PAW_Vector side4 = {4, {-a_length, 0, 0, 0}};
	PAW_Vector side5 = {4, {0, -a_length, 0, 0}};
	PAW_Vector side6 = {4, {0, 0, -a_length, 0}};
	PAW_Square square4 = {corner2, {side4, side5}, 1, texture4};
	PAW_Figure_push_square(figure, square4);
	PAW_Square square5 = {corner2, {side4, side6}, 1, texture5};
	PAW_Figure_push_square(figure, square5);
	PAW_Square square6 = {corner2, {side5, side6}, 1, texture6};
	PAW_Figure_push_square(figure, square6);
}


PAW_Vector PAW_Figure_toShip(PAW_Figure* const figure, const float a_width, const uint32_t a_color)
{
	for(size_t i =0 ; i < 4; ++i)
	{
		figure->elements[i] = 0;
	}
	figure->flag=1;
	const float width= 1.0f * a_width;
	const float scale=1.5f;

	PAW_Vector P1 = {3, {width, 35*scale, 0.0f}};
	PAW_Vector P2 = {3, {width+4*scale, 29*scale, 0.0f}};
	PAW_Vector P3 = {3, {width+6*scale, 29*scale, 0.0f}};
	PAW_Vector P4 = {3, {width+6*scale, 33.7*scale, 0.0f}};
	PAW_Vector P5 = {3, {width+12*scale, 29*scale, 0.0f}};
	PAW_Vector P6 = {3, {width+8*scale, 20*scale, 0.0f}};
	PAW_Vector P7 = {3, {width+12*scale, 11*scale, 0.0f}};
	PAW_Vector P8 = {3, {width+4*scale, 11*scale, 0.0f}};
	PAW_Vector P9 = {3, {width, 5*scale, 0.0f}};
	PAW_Vector P10 = {3, {width-4*scale, 11*scale, 0.0f}};
	PAW_Vector P11 = {3, {width-12*scale, 11*scale, 0.0f}};
	PAW_Vector P12 = {3, {width-8*scale, 20*scale, 0.0f}};
	PAW_Vector P13 = {3, {width-12*scale, 29*scale, 0.0f}};
	PAW_Vector P14 = {3, {width-6*scale, 29*scale, 0.0f}};
	PAW_Vector P15 = {3, {width-6*scale, 33.7*scale, 0.0f}};
	PAW_Vector P16 = {3, {width-4*scale, 29*scale, 0.0f}};

	PAW_Line L1 = {a_color, false, P1, P2};
	PAW_Line L2 = {a_color, false, P2, P3};
	PAW_Line L3 = {a_color, false, P3, P4};
	PAW_Line L4 = {a_color, false, P3, P5};
	PAW_Line L5 = {a_color, false, P5, P6};
	PAW_Line L6 = {a_color, false, P6, P7};
	PAW_Line L7 = {a_color, false, P7, P8};
	PAW_Line L8 = {a_color, false, P8, P9};
	PAW_Line L9 = {a_color, false, P9, P10};
	PAW_Line L10 = {a_color, false, P10, P11};
	PAW_Line L11 = {a_color, false, P11, P12};
	PAW_Line L12 = {a_color, false, P12, P13};
	PAW_Line L13 = {a_color, false, P13, P14};
	PAW_Line L14 = {a_color, false, P14, P15};
	PAW_Line L15 = {a_color, false, P14, P16};
	PAW_Line L16 = {a_color, false, P16, P1};


	PAW_Figure_push_line(figure, L1);
	PAW_Figure_push_line(figure, L2);
	PAW_Figure_push_line(figure, L3);
	PAW_Figure_push_line(figure, L4);
	PAW_Figure_push_line(figure, L5);
	PAW_Figure_push_line(figure, L6);
	PAW_Figure_push_line(figure, L7);
	PAW_Figure_push_line(figure, L8);
	PAW_Figure_push_line(figure, L9);
	PAW_Figure_push_line(figure, L10);
	PAW_Figure_push_line(figure, L11);
	PAW_Figure_push_line(figure, L12);
	PAW_Figure_push_line(figure, L13);
	PAW_Figure_push_line(figure, L14);
	PAW_Figure_push_line(figure, L15);
	PAW_Figure_push_line(figure, L16);

	PAW_Vector Data_for_collision={3, {width, 20*scale, 15*scale}}; // dane do kolizji w postaci wspolrzedna X, wspolrzedna Y, promien
	return(Data_for_collision);

}

// PAW_Vector PAW_Figure_toMeteor(PAW_Figure* const figure, const uint16_t min_x, const uint16_t max_x, const uint16_t min_y, const uint16_t max_y, const uint16_t min_r, const uint16_t max_r, const uint32_t a_color){
// 	for(size_t i =0 ; i < 4; ++i)
// 		{
// 			figure->elements[i] = 0;
// 		}
// 		figure->flag=2;
// 	const uint32_t black = 0xFF000000;//{255,0,0,0};
// 	uint16_t x=rand_uint16_t(min_x, max_x)*1.0f;
// 	uint16_t y=rand_uint16_t(min_y, max_y)*1.0f;
// 	uint16_t r=rand_uint16_t(min_r, max_r)*1.0f;

// 	PAW_Vector center = {2, {x, y, 0.0f}};
// 	PAW_Circle circle = {black, true, r, center};
// 	PAW_Circle_push_circle(&figure, circle);
// 	PAW_Vector Data_for_collision={3, {x, y, r}}; // dane do kolizji w postaci wspolrzedna X, wspolrzedna Y, promien
// 	return(Data_for_collision);
// }

void PAW_Figure_toMeteor(PAW_Figure* const figure, const uint16_t x, const uint16_t y, const uint16_t r, const uint32_t a_color){
	for(size_t i =0 ; i < 4; ++i)
			{
				figure->elements[i] = 0;
			}
	figure->flag=2;
	PAW_Vector center = {2, {x, y, 0.0f}};
	PAW_Circle circle = {a_color, false, r, center};
	PAW_Figure_push_circle(figure, circle);
}

// ponizsza funkcja do prawidlowego dzialania wymaga sceny o wymiarze 240x320
void PAW_Figure_animation_meteor(PAW_Figure* const figure, const float fall_speed){
	uint16_t x, r;
	PAW_Vector translation = {2, {0.0f, -fall_speed*1.0f, 0.0f}};
	PAW_Figure_translate(figure, &translation);
	if (figure->circles->center.data[1] < 0.0f){
		r=rand_uint16_t(5, 40)*1.0f;                        	// losowanie promienia nowego meteorytu
		x=rand_uint16_t(0+r, 240-r)*1.0f;						// losowanie szerokosci, tak by nie wychodzic poza scene
		//PAW_Vector translation = {2, {x, 320.0f, 0.0f}};	// ten sposob przemieszczania sprawial, ze po pewnym czasie bledy sie nakladaly, i przestawala dzialac animacja i wykrywanie kolizji
		figure->circles->center.data[1] = 320.0f;
		figure->circles->center.data[0] = x; 			// to dziala duzo lepiej
		PAW_Figure_translate(figure, &translation);
		figure->circles->radius = r;

	}

}

void PAW_Figure_l3gd20_animation_ship(PAW_Figure* const figure, SPI_HandleTypeDef hspi_in){

	uint8_t data = GET_Y_H(hspi_in);
	float speed_ship=0.0f;
			if (data<128){  //w lewo
				speed_ship = (data+1)/5*1.0f;    // zwiekszona czulosc, by ulatwic sterowanie
			}else{   		// w prawo
				speed_ship = (data%128-128)/5*1.0f;
			}
			if (data==255){ //brak ruchu
				speed_ship = 0.0f;
			}
			PAW_Vector translation = {3, {speed_ship, 0.0f, 0.0f}};
			PAW_Figure_translate(figure, &translation);
}

boolean PAW_Figure_Check_collision(PAW_Figure* const ship, PAW_Figure* const meteor){
	uint16_t x_ship = ship->lines[0].begin.data[0];			//z czolowego punktu statku dostajemy sie do środka statku i aproksymujemy przez okrąg
	uint16_t y_ship = ship->lines[0].begin.data[1]-22.5;  		 //modyfikator -22.5 zalezy od skali(-15*scale), to trzeba bedzie jeszcze jakos uniezaleznic
	uint16_t r_ship = 22.5;
	uint16_t x_meteor = meteor->circles->center.data[0];
	uint16_t y_meteor = meteor->circles->center.data[1];
	uint16_t r_meteor = meteor->circles->radius;
	if (((x_ship-x_meteor)*(x_ship-x_meteor)+(y_ship-y_meteor)*(y_ship-y_meteor))<((r_ship+r_meteor)*(r_ship+r_meteor))){
		return true;                                    // zamiast brac pierwiastek z lewej strony nierownosci
	}else{							// podnosze druga strone do kwadratu
		return false;
	}
}

void PAW_Figure_clearTextures(PAW_Figure* const figure)
{
	for (size_t i = 0; i <figure->elements[3]; ++i)
	{
		PAW_Texture_clear(&figure->squares[i].texture);
	}
}
