#ifndef PAW_BUFFER_H_
#define PAW_BUFFER_H_

#define VIDEO_RAM 0xD0000000

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"

inline uint32_t PAW_Buffer_Switch();
inline void PAW_Write_To_Buffer(const uint32_t buffer,const uint16_t Xpos,const uint16_t Ypos,const uint32_t RGB_Code);
void PAW_Buffer_init();

#endif /* PAW_BUFFER_H_ */
