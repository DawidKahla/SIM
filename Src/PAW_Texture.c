#include "PAW_Texture.h"

void PAW_Texture_prepare(PAW_Texture* texture, size_t height, size_t width, uint32_t background)
{
	texture->width = width;
	texture->height = height;
	texture->pixels = malloc(width * height * sizeof(uint32_t));
	for(size_t i = 0; i < width * height; ++i)
	{
		texture->pixels[i] = background;
	}

}

uint32_t* PAW_Texture_at(PAW_Texture* texture, size_t i, size_t j)
{
	if (i < texture->height && j < texture->width)
	{
		return &texture->pixels[i * texture->width + j];
	}
	return NULL;
}

void PAW_Texture_clear(PAW_Texture* texture)
{
	free(texture->pixels);
}
