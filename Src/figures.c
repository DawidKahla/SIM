
#include "figures.h"


void PAW_MakeFeatherFromFigure(PAW_Figure* figure)
{
	PAW_Vector temp1 = {3, {120.0f, 90.0f, 0.0f}};
	PAW_Vector temp2 = {3, {120.0f, 90.0f + 50.0f, 0.0f}};
	PAW_Vector temp3 = {3, {120.0f, 90.0f + 50.0f + 40.0f, 0.0f}};
	PAW_Vector temp4 = {3, {120.0f,
			90.0f + 50.0f + 40.0f + 30.0f, 0.0f}};
	PAW_Vector temp5 = {3, {120.0f,
			90.0f + 50.0f + 40.0f + 30.0f + 30.0f, 0.0f}};

	PAW_Circle big_cir1 = {0xff00ff00, true, 35.0f, temp1};
	PAW_Circle big_cir2 = {0xff0000ff, true, 20.0f, temp1};

	PAW_Circle mid_cir1 = {0xff00ff00, true, 30.0f, temp2};
	PAW_Circle mid_cir2 = {0xff0000ff, true, 15.0f, temp2};

	PAW_Circle s_cir1 = {0xff00ff00, true, 25.0f, temp3};
	PAW_Circle s_cir2 = {0xff0000ff, true, 15.0f, temp3};
	PAW_Circle s_cir3 = {0xff00ff00, true, 20.0f, temp4};
	PAW_Circle s_cir4 = {0xff0000ff, true, 10.0f, temp4};
	PAW_Circle s_cir5 = {0xff00ff00, true, 20.0f, temp5};
	PAW_Circle s_cir6 = {0xff0000ff, true, 10.0f, temp5};

	PAW_Figure_push_circle(figure, big_cir1);
	PAW_Figure_push_circle(figure, big_cir2);
	PAW_Figure_push_circle(figure, mid_cir1);
	PAW_Figure_push_circle(figure, mid_cir2);
	PAW_Figure_push_circle(figure, s_cir1);
	PAW_Figure_push_circle(figure, s_cir2);
	PAW_Figure_push_circle(figure, s_cir3);
	PAW_Figure_push_circle(figure, s_cir4);
	PAW_Figure_push_circle(figure, s_cir5);
	PAW_Figure_push_circle(figure, s_cir6);

}


void PAW_MakeStarFromFigure(PAW_Figure* const figure, const PAW_Vector position,
		const float radius, const uint32_t color)
{
	PAW_Vector gw1 = {3, {0.0f, radius, 0.0f}};
	PAW_Vector gw2 = {3, {radius * sqrt(3) / 2.0f,
			radius / 2.0f, 0.0f}};
	PAW_Vector gw3 = {3, {-radius * sqrt(3) / 2.0f,
			radius / 2.0f, 0.0f}};

	PAW_Vector temp1 = PAW_Vector_sub(&position, &gw1);
	PAW_Vector temp2 = PAW_Vector_add(&position, &gw1);
	PAW_Vector temp3 = PAW_Vector_sub(&position, &gw2);
	PAW_Vector temp4 = PAW_Vector_add(&position, &gw2);
	PAW_Vector temp5 = PAW_Vector_sub(&position, &gw3);
	PAW_Vector temp6 = PAW_Vector_add(&position, &gw3);

	PAW_Line line1 = {color, false, temp1, temp2};
	PAW_Line line2 = {color, false, temp3, temp4};
	PAW_Line line3 = {color, false, temp5, temp6};
	PAW_Figure_push_line(figure, line1);
	PAW_Figure_push_line(figure, line2);
	PAW_Figure_push_line(figure, line3);

/*
	PAW_Vector3D_destr(gw1);
	PAW_Vector3D_destr(gw2);
	PAW_Vector3D_destr(gw3);
	PAW_Vector3D_destr(temp1);
	PAW_Vector3D_destr(temp2);
	PAW_Vector3D_destr(temp3);
	PAW_Vector3D_destr(temp4);
	PAW_Vector3D_destr(temp5);
	PAW_Vector3D_destr(temp6);*/
}

void PAW_MakeDonutFromFigure(PAW_Figure* const figure, PAW_Vector* const position,
		const float radius1, const float radius2, const uint32_t color)
{
	PAW_Circle circle1 = {true, color, radius1, *position};
	PAW_Circle circle2 = {true, color, radius2, *position};
	PAW_Figure_push_circle(figure, circle1);
	PAW_Figure_push_circle(figure, circle2);
}

