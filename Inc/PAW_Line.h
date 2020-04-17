#ifndef PAW_LINE_H
#define PAW_LINE_H

#include "PAW_Matrix.h"
#include "PAW_Texture.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint32_t color;
	char is_filled;
	PAW_Vector begin;
	PAW_Vector end;
}PAW_Line;

void PAW_Line_change_color(PAW_Line* const line, const uint32_t color);

void PAW_Line_show(const PAW_Line* const line, const uint32_t buffer);
void PAW_Line_drawOnTexture(const PAW_Line* const line, PAW_Texture* texture);

void PAW_Line_rotate(PAW_Line* const line, const PAW_Vector* const rotate_point, const int16_t degrees);
void PAW_Line_translate(PAW_Line* const line, const PAW_Vector* const translation);

void PAW_Line_rotate_helper(PAW_Line* const line, const PAW_Matrix* const rotation_matrix);
void PAW_Line_projection_helper(PAW_Line* const line, const PAW_Matrix* const projection_matrix);
void PAW_Line_scale_helper(PAW_Line* const line, const float scale);

#ifdef __cplusplus
}
#endif

#endif //PAW_LINE_H
