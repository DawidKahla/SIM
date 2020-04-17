#include "PAW_Buffer.h"


uint32_t buffer1;
uint32_t buffer2;

uint32_t active_buffer;

extern DMA_HandleTypeDef hdma_memtomem_dma2_stream0;

void PAW_Buffer_init(){
	buffer1 = 0xD0000000;
	buffer2 = 0xD0000000 + 0x258000;
	active_buffer = buffer1;
}

uint32_t PAW_Buffer_Switch(){
	if (active_buffer == buffer2){
		active_buffer = buffer1;
	}
	else{
		active_buffer = buffer2;
		}
	return active_buffer;
}

void PAW_Write_To_Buffer(const uint32_t buffer,const uint16_t Xpos,const uint16_t Ypos,const uint32_t RGB_Code){
	*(__IO uint32_t*) (buffer + (sizeof(uint32_t)*(Ypos*BSP_LCD_GetXSize() + Xpos)) ) = RGB_Code;
}


