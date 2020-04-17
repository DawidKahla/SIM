#ifndef PAW_CIRCLE_H
#define PAW_CIRCLE_H

#include "PAW_Line.h"
#include "PAW_Vector.h"
#include "PAW_Matrix.h"
#include "PAW_Texture.h"

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PAW_Circle
{
	uint32_t color;
	char is_filled;
	float radius;
	PAW_Vector center;
}PAW_Circle;

void PAW_Circle_show(PAW_Circle* const circle, const uint32_t buffer);
void PAW_Circle_drawOnTexture(PAW_Circle* const circle, PAW_Texture* texture);

void PAW_Circle_rotate(PAW_Circle* const circle, const PAW_Vector* const rotate_point,
		const int16_t degrees);
void PAW_Circle_translate(PAW_Circle* const circle, const PAW_Vector* const translation);

void PAW_Circle_rotate_helper(PAW_Circle* const circle, const PAW_Matrix* const rotation_matrix);
void PAW_Circle_projection_helper(PAW_Circle* const circle, const PAW_Matrix* const projection_matrix);
void PAW_Circle_scale_helper(PAW_Circle* const circle, const float scale);

#ifdef __cplusplus
}
#endif

#endif //PAW_CIRCLE_H
