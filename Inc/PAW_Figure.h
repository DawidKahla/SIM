#ifndef PAW_FIGURE_H
#define PAW_FIGURE_H

#include <stdlib.h>
#include <time.h>

#include "PAW_3D_Projection.h"
#include "PAW_Circle.h"
#include "PAW_Line.h"
#include "PAW_Point.h"
#include "PAW_Square.h"
#include "PAW_Vector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint16_t size;
	uint16_t elements[4]; // [0] - circles
							//[1] - points
							//[2] - lines
							//[3] - squares
	PAW_Circle* circles;
	PAW_Point* points;
	PAW_Line* lines;
	PAW_Square* squares;
	uint16_t flag; // 0 - inne // 1 - statek // 2 - meteor
}PAW_Figure;

void PAW_Figure_push(void * element);

PAW_Figure PAW_Figure_create(const uint16_t circles, const uint16_t points, const uint16_t lines, const uint16_t squares);

void PAW_Figure_destr(PAW_Figure* figure);
void PAW_Figure_push_circle(PAW_Figure* const figure, PAW_Circle const n_circle);
void PAW_Figure_push_point(PAW_Figure* const figure, PAW_Point const n_points);
void PAW_Figure_push_line(PAW_Figure* const figure, PAW_Line const n_line);
void PAW_Figure_push_square(PAW_Figure* const figure, PAW_Square const n_square);

void PAW_Figure_show(const PAW_Figure* const figure, const uint32_t buffer);

void PAW_Figure_translate(PAW_Figure* const figure, const PAW_Vector* const n_translation);
void PAW_Figure_rotate(PAW_Figure* const figure, const PAW_Vector* const rotate_point, const int16_t degrees);

void PAW_Figure_project3D_to_2D(PAW_Figure* const figure);
PAW_Figure PAW_Figure_project3D_to_2D_new(PAW_Figure* const figure);
void PAW_Figure_rotate3D(PAW_Figure* const figure, const float x_degrees, const float y_degrees, const float z_degrees);
void PAW_Figure_scale3D(PAW_Figure* const figure, const float scale);
void PAW_Figure_toCube(PAW_Figure* const figure, const float a_length, const uint32_t a_color);
void PAW_Figure_toPyramid(PAW_Figure* const figure, const float a_length, const uint32_t a_color);
void PAW_Figure_toCross(PAW_Figure* const figure, const float a_length, const uint32_t a_color);

void PAW_Figure_toTexturedCube(PAW_Figure* const figure, const float a_length, const uint32_t a_color);
void PAW_Figure_toDice(PAW_Figure* const figure, const float a_length, const uint32_t a_color);

void PAW_Figure_toExperimental(PAW_Figure* const figure, const float a_length, const uint32_t a_color);

void PAW_Figure_paint(PAW_Figure* const figure, const PAW_Line* const, const PAW_Line* const, const uint32_t a_color);

void PAW_Figure_clearTextures(PAW_Figure* const figure);

/* DK SIM */
void PAW_Figure_toShip(PAW_Figure* const figure, const float a_width, const uint32_t a_color);
//PAW_Vector PAW_Figure_toMeteor(PAW_Figure* const figure, const uint16_t min_x, const uint16_t max_x, const uint16_t min_y, const uint16_t max_y, const uint16_t min_r, const uint16_t max_r, const uint32_t a_color);
void PAW_Figure_toMeteor(PAW_Figure* const figure, const uint16_t x, const uint16_t y, const uint16_t r, const uint32_t a_color);
void PAW_Figure_l3gd20_animation_ship(PAW_Figure* const figure, SPI_HandleTypeDef hspi_in);
void PAW_Figure_animation_meteor(PAW_Figure* const figure, const float fall_speed);
boolean PAW_Figure_Check_collision(PAW_Figure* const ship, PAW_Figure* const meteor);
	
#ifdef __cplusplus
}
#endif

#endif //PAW_FIGURE_H
