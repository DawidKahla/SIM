#ifndef PAW_TEXTURE_H_
#define PAW_TEXTURE_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct {
	uint32_t* pixels;
	size_t width;
	size_t height;
	char allocated;
} PAW_Texture;

void PAW_Texture_prepare(PAW_Texture*, size_t height, size_t width, uint32_t background);
uint32_t* PAW_Texture_at(PAW_Texture* texture, size_t i, size_t j);
void PAW_Texture_clear(PAW_Texture* texture);

#endif /* PAW_TEXTURE_H_ */
