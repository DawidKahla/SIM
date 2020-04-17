#include "PAW_Scene.h"

PAW_Scene PAW_Scene_create(const float n_size_x, const float n_size_y,
	const uint32_t n_size, const uint32_t n_bg){

	PAW_Scene scene;

	scene.background = n_bg;
	scene.elements = 0;
	scene.size = n_size;
	scene.size_x = n_size_x;
	scene.size_y = n_size_y;
	scene.figures = malloc( n_size * sizeof(PAW_Figure));
	return scene;

}

void PAW_Scene_destr(PAW_Scene* scene)
{
	for(uint i = 0; i< scene->elements; i++)
		PAW_Figure_destr(&scene->figures[i]);
	free(scene->figures);
}

PAW_Scene PAW_Scene_create_default_size(const uint32_t n_background, const uint32_t n_size)
{
	PAW_Scene scene = PAW_Scene_create(240, 320, n_size, n_background);
	return scene;

}

void PAW_Scene_push(PAW_Scene* const scene, const PAW_Figure n_figure){
	scene->figures[scene->elements] = n_figure;
	scene->elements++;
}


void display_background(const uint32_t background, const uint32_t buffer)
{
	for (uint32_t i = 0; i <= 240; ++i)
	{
		for (uint32_t j = 0; j <= 320; ++j)
		{
			PAW_Write_To_Buffer(buffer, i, j, background);
		}
	}
}

void PAW_Scene_display(const PAW_Scene scene)
{
	uint32_t buffer = PAW_Buffer_Switch();
	display_background(scene.background, buffer);
	for (size_t i = 0; i < scene.elements; ++i)
	{
		PAW_Figure_show(&scene.figures[i], buffer);
	}
	BSP_LCD_LayerDefaultInit(0x1, buffer);
}


