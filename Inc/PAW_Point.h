#ifndef PAW_POINT_H
#define PAW_POINT_H

#include "PAW_Matrix.h"
#include "PAW_Texture.h"
#include <stdlib.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PAW_Point {
	PAW_Vector position;
	char is_filled;
	uint32_t color;
}PAW_Point;

void PAW_Point_change_color(PAW_Point* const point, const uint32_t n_color);

void PAW_Point_show(const PAW_Point* const point, const uint32_t buffer);
void PAW_Point_drawOnTexture(const PAW_Point* const point, PAW_Texture* texture);

void PAW_Point_rotate(PAW_Point* const point, const PAW_Vector* const rotate_point, const int16_t degrees);
void PAW_Point_translate(PAW_Point* const point, const PAW_Vector* const translation);

void PAW_Point_rotate_helper(PAW_Point* const point, const PAW_Matrix* const rotation_matrix);
void PAW_Point_projection_helper(PAW_Point* const point, const PAW_Matrix* const projection_matrix);
void PAW_Point_scale_helper(PAW_Point* const point, const float scale);

#ifdef __cplusplus
}
#endif

#endif //PAW_POINT_H
