#ifndef PAW_Scene_H
#define PAW_Scene_H

#include "PAW_Figure.h"
#include "PAW_Buffer.h"
#include "main.h"
#include "stm32f429i_discovery_sdram.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct PAW_Scene {
	float size_x, size_y;
	uint32_t background;
	uint32_t size;
	uint32_t elements;
	PAW_Figure* figures;
	//dodane DK

}PAW_Scene;


PAW_Scene PAW_Scene_create(const float n_size_x, const float n_size_y,
	const uint32_t n_size, const uint32_t n_bg);
void PAW_Scene_destr(PAW_Scene* scene);

void PAW_Scene_push(PAW_Scene* const scene, const PAW_Figure n_figure);

PAW_Scene PAW_Scene_create_default_size(const uint32_t n_background, const uint32_t n_size);
void PAW_Scene_display(PAW_Scene scene);

#endif //PAW_Scene_H
