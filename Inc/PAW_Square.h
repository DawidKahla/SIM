#ifndef PAW_SQUARE_H
#define PAW_SQUARE_H

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

typedef struct PAW_Square {
	PAW_Vector corner;
	PAW_Vector side[2];
	char has_texture;
	PAW_Texture texture;
}PAW_Square;

void PAW_Square_show(PAW_Square* const square, uint32_t buffer);

void PAW_Square_rotate(PAW_Square* const square, const PAW_Vector* const rotate_point,
		const int16_t degrees);
void PAW_Square_translate(PAW_Square* const square, const PAW_Vector* const translation);

void PAW_Square_rotate_helper(PAW_Square* const square, const PAW_Matrix* const rotation_matrix);
void PAW_Square_projection_helper(PAW_Square* const square, const PAW_Matrix* const projection_matrix);
void PAW_Square_scale_helper(PAW_Square* const square, const float scale);

#ifdef __cplusplus
}
#endif

#endif // PAW_SQUARE_H
