/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <time.h>
#include "stm32f4xx_hal_ltdc.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_sdram.h"
#include "stm32f429i_discovery.h"


#include "PAW_Circle.h"
#include "PAW_Buffer.h"
#include "PAW_Figure.h"
#include "PAW_Line.h"
#include "PAW_Math.h"
#include "PAW_Matrix.h"
#include "PAW_Point.h"
#include "PAW_Scene.h"
#include "PAW_Vector.h"
#include "figures.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

SPI_HandleTypeDef hspi5;

DMA_HandleTypeDef hdma_memtomem_dma2_stream0;
SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
volatile const uint32_t fps = 30;
volatile uint8_t demo_number = 0;
volatile uint32_t old_time = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_I2C3_Init(void);
static void MX_LTDC_Init(void);
static void MX_SPI5_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
/*void HAL_GPIO_EXTI_Callback (uint16_t GPIO_Pin){
	if((GPIO_Pin == B1_Pin) && ((HAL_GetTick() - old_time) >200)){
		old_time = HAL_GetTick();
		demo_number++;
		demo_number %= 5;
	}

} */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void demo(){
	int8_t yaw1 = -1;
	int8_t yaw2 = 2;

		const uint32_t green = 0xFF55FF33;//{255,85,255,51};
		const uint32_t black = 0xFF000000;//{255,0,0,0};
		const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
		const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
		const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
		const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};

		const PAW_Vector display_center = {3, {120, 160, 1.0}};

		PAW_Scene PAW_demo = PAW_Scene_create_default_size(green, 32);
		PAW_Figure p = PAW_Figure_create(1, 0, 1, 0);
		PAW_Vector p_o_center  = {2, {200.0f, 100.0f, 0.0f}};
		PAW_Vector p_begin = {3, {210.0f, 120.0f, 0.0f}};
		PAW_Vector p_end = {3, {210.0f, 30.0f, 0.0f}};
		PAW_Line p_line = {*(uint32_t*)blue, false, p_begin, p_end};
		PAW_Circle p_circle = {*(uint32_t*)green, false, 30, p_o_center};

		PAW_Figure_push_circle(&p, p_circle);
		PAW_Figure_push_line(&p, p_line);
		PAW_Scene_push(&PAW_demo, p);

		PAW_Figure A = PAW_Figure_create(0, 0, 3, 0);
		PAW_Vector A_begin = {3, {180.0f, 30.0f, 0.0f}};
		PAW_Vector A_end = {3, {120.0f, 30.0f, 0.0f}};
		PAW_Vector A_top = {3, {150, 120, 0}};
		PAW_Vector A_mid1 = {3, {165, 75, 0}};
		PAW_Vector A_mid2 = {3, {135, 75, 0}};
		PAW_Line A_line1 = {red, false, A_begin, A_top};
		PAW_Line A_line2 = {red, false, A_top, A_end};
		PAW_Line A_line_mid = {blue, false, A_mid1, A_mid2};

		PAW_Figure_push_line(&A, A_line1);
		PAW_Figure_push_line(&A, A_line2);
		PAW_Figure_push_line(&A, A_line_mid);

		PAW_Scene_push(&PAW_demo, A);

		PAW_Figure W = PAW_Figure_create(0, 0, 5, 0);
		PAW_Vector W_begin = {3, {120, 120, 0}};
		PAW_Vector W_end = {3, {40, 120, 0}};
		PAW_Vector W_top = {3, {80, 120, 0}};
		PAW_Vector W_bot1 = {3, {100, 30, 0}};
		PAW_Vector W_bot2 = {3, {60, 30, 0}};
		PAW_Line W_line1 = {black, false, W_begin, W_bot1};
		PAW_Line W_line2 = {black, false, W_bot1, W_top};
		PAW_Line W_line3 = {black, false, W_top, W_bot2};
		PAW_Line W_line4 = {black, false, W_bot2, W_end};


		PAW_Figure_push_line(&W, W_line2);
		PAW_Figure_push_line(&W, W_line3);
		PAW_Figure_push_line(&W, W_line4);
		PAW_Figure_push_line(&W, W_line1);
		PAW_Scene_push(&PAW_demo, W);

		PAW_Vector star_center = {3, {150, 250, 1.0}};
		PAW_Figure star = PAW_Figure_create(0, 0, 3, 0);
		PAW_Figure star2 = PAW_Figure_create(0, 0, 3, 0);
		PAW_MakeStarFromFigure(&star, star_center, 35, *(uint32_t*)black);
		PAW_MakeStarFromFigure(&star2, star_center, 25, *(uint32_t*)yellow);

		PAW_Scene_push(&PAW_demo, star);
		PAW_Scene_push(&PAW_demo, star2);

		while(demo_number == 0){
			PAW_Scene_display(PAW_demo);
			PAW_Figure_rotate(&star, &display_center, yaw1);
			PAW_Figure_rotate(&star2, &display_center, yaw2);
		}
		PAW_Scene_destr(&PAW_demo);

}

//void demo1()
//{
//		const uint32_t green = 0xFF55FF33;//{255,85,255,51};
//		const uint32_t black = 0xFF000000;//{255,0,0,0};
//		const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
//		const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
//		const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
//		const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};
//
//		srand((unsigned)time(0));
//		PAW_Scene scenka = PAW_Scene_create(240, 320, 25, 0xFFFFFFFF);
//
//		PAW_Figure experyment = PAW_Figure_create(0, 0, 200, 0);
//
//		int i = 0;
//
//		while(demo_number == 1)
//		{
//			i%=360;
//			scenka.elements = 0;
//
//
//				PAW_Figure_toExperimental(&experyment, 50.0f, black);
//				PAW_Figure_scale3D(&experyment, 1.5f);
//				PAW_Figure_rotate3D(&experyment, (float)i, (float)i,(float)i);
//				PAW_Figure_project3D_to_2D(&experyment);
//				PAW_Vector translation = {4, {120.0f,120.0f,60.0f,1.0f}};
//				PAW_Figure_translate(&experyment, &translation);
//				PAW_Scene_push(&scenka, experyment);
//
//				PAW_Scene_display(scenka);
//				i+=5;
//				HAL_Delay(1000/fps);
//		}
//		//PAW_Figure_destr(&experyment);
//		PAW_Scene_destr(&scenka);
//}
//
//void demo2()
//{
//	const uint32_t green = 0xFF55FF33;//{255,85,255,51};
//	const uint32_t black = 0xFF000000;//{255,0,0,0};
//	const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
//	const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
//	const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
//	const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};
//
//	srand((unsigned)time(0));
//	PAW_Scene scenka = PAW_Scene_create(240, 320, 25, 0xFFFFFFFF);
//
//	PAW_Figure cube = PAW_Figure_create(0, 0, 0, 6);
//
//	int i = 0;
//
//	while(demo_number==2)
//	{
//		i%=360;
//		scenka.elements = 0;
//
//		PAW_Figure_toDice(&cube, 70, 0);
//
//		PAW_Figure_rotate3D(&cube, (float)i, (float)i,(float)i);
//		PAW_Figure_project3D_to_2D(&cube);
//		PAW_Vector translation = {4, {100.0f,150.0f,0.0f,1.0f}};
//		PAW_Figure_translate(&cube, &translation);
//		PAW_Scene_push(&scenka, cube);
//
//		PAW_Scene_display(scenka);
//		PAW_Figure_clearTextures(&cube);
//		i+=5;
//		HAL_Delay(1000/fps);
//	}
//	PAW_Scene_destr(&scenka);
//}
//
//void demo3()
//{
//	const uint32_t green = 0xFF55FF33;//{255,85,255,51};
//	const uint32_t black = 0xFF000000;//{255,0,0,0};
//	const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
//	const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
//	const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
//	const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};
//
//	srand((unsigned)time(0));
//	PAW_Scene scenka = PAW_Scene_create(240, 320, 25, 0xFFFFFFFF);
//
//	PAW_Figure cube = PAW_Figure_create(0, 0, 0, 6);
//
//	int i = 0;
//
//	PAW_Figure_toDice(&cube, 70, 0);
//
//	while(demo_number==3)
//	{
//		i%=360;
//		scenka.elements = 0;
//		PAW_Figure_rotate3D(&cube, (float)5, (float)5,(float)5);
//		PAW_Figure cube2d = PAW_Figure_project3D_to_2D_new(&cube);
//		PAW_Vector translation = {4, {100.0f,150.0f,0.0f,1.0f}};
//		PAW_Figure_translate(&cube2d, &translation);
//		PAW_Scene_push(&scenka, cube2d);
//
//		PAW_Scene_display(scenka);
//		i+=5;
//		HAL_Delay(1000/fps);
//		PAW_Figure_destr(&cube2d);
//	}
//	PAW_Figure_clearTextures(&cube);
//	PAW_Scene_destr(&scenka);
//}

void demo4()
{
		const uint32_t green = 0xFF55FF33;//{255,85,255,51};
		const uint32_t black = 0xFF000000;//{255,0,0,0};
		const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
		const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
		const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
		const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};

		PAW_Scene scenka = PAW_Scene_create(240, 320, 25, 0xFFFFFFFF);

		PAW_Figure statek = PAW_Figure_create(0, 0, 16, 0);

		PAW_Figure_toShip(&statek, 120, black);

		PAW_Scene_push(&scenka, statek);
		PAW_Figure meteor1 = PAW_Figure_create(1, 0, 0, 0);
		PAW_Figure meteor2 = PAW_Figure_create(1, 0, 0, 0);
		PAW_Figure meteor3 = PAW_Figure_create(1, 0, 0, 0);
		PAW_Figure meteor4 = PAW_Figure_create(1, 0, 0, 0);
		PAW_Figure_toMeteor(&meteor1, 60, 80, 20, red);
		PAW_Figure_toMeteor(&meteor2, 200, 220, 20, green);
		PAW_Figure_toMeteor(&meteor3, 80, 300, 20, blue);
		PAW_Figure_toMeteor(&meteor4, 140, 160, 20, yellow);
		PAW_Scene_push(&scenka, meteor1);
		PAW_Scene_push(&scenka, meteor2);
		PAW_Scene_push(&scenka, meteor3);
		PAW_Scene_push(&scenka, meteor4);

		float animation_speed=1.001;
		uint32_t score;
		while(/*demo_number == 4*/ true){
					PAW_Scene_display(scenka);
					PAW_Figure_l3gd20_animation_ship(&statek, hspi5);  		// animacja statku została zwielokrotniona, aby
					PAW_Figure_animation_meteor(&meteor1, animation_speed);	// zmniejszyc efekt lagow
					PAW_Figure_animation_meteor(&meteor2, animation_speed);
					PAW_Figure_l3gd20_animation_ship(&statek, hspi5);
					PAW_Figure_animation_meteor(&meteor3, animation_speed);
					PAW_Figure_animation_meteor(&meteor4, animation_speed);
					if (animation_speed < 32){
						animation_speed=animation_speed*1.001;
		}else{
			score=3468;
		}
		PAW_Scene_destr(&scenka);

}

//void demo4()
//{
//		const uint32_t green = 0xFF55FF33;//{255,85,255,51};
//		const uint32_t black = 0xFF000000;//{255,0,0,0};
//		const uint32_t white = 0xFFFFFFFF;//{255,255,255,255};
//		const uint32_t red = 0xFFE81717;//{ 255,232,23,23};
//		const uint32_t blue = 0xFF177FE9;//{255,23,127,232};
//		const uint32_t yellow = 0xFFE8A017;//{255,232,210,23};
//
//		PAW_Scene scenka = PAW_Scene_create(240, 320, 25, 0xFFFFFFFF);
//
//		PAW_Figure statek = GAME_Ship_create(1.5, 120.0, 5.0);
//
//		GAME_Ship_draw(&statek, black);
//
//		PAW_Scene_ship(&scenka, statek);
//		while(demo_number == 4){
//					PAW_Scene_display(scenka);
//		}
//		PAW_Scene_destr(&scenka);
//
//}

/* *
 * @brief  HAL SDRAM State structure definition
 * /
 typedef enum
 {
 HAL_SDRAM_STATE_RESET             = 0x00U,  / *!< SDRAM not yet initialized or disabled * /
 HAL_SDRAM_STATE_READY             = 0x01U,  / *!< SDRAM initialized and ready for use   * /
 HAL_SDRAM_STATE_BUSY              = 0x02U,  / *!< SDRAM internal process is ongoing     * /
 HAL_SDRAM_STATE_ERROR             = 0x03U,  / *!< SDRAM error state                     * /
 HAL_SDRAM_STATE_WRITE_PROTECTED   = 0x04U,  / *!< SDRAM device write protected          * /
 HAL_SDRAM_STATE_PRECHARGED        = 0x05U   / *!< SDRAM device precharged               * /

 }HAL_SDRAM_StateTypeDef;*/


void led_sdram_reset(void)
{
	if (hsdram1.State == HAL_SDRAM_STATE_RESET)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_Delay(250);
	}
}

void led_sdram_ready()
{
	if (hsdram1.State == HAL_SDRAM_STATE_READY)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
	}
}

void led_sdram_busy()
{
	if (hsdram1.State == HAL_SDRAM_STATE_BUSY)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

void led_sdram_error()
{
	if (hsdram1.State == HAL_SDRAM_STATE_ERROR)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(250);
	}
}

void led_sdram_write_protected()
{
	if (hsdram1.State == HAL_SDRAM_STATE_WRITE_PROTECTED)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_Delay(1000);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

void led_sdram_precharged()
{
	if (hsdram1.State == HAL_SDRAM_STATE_PRECHARGED)
	{
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
		HAL_Delay(250);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
		HAL_Delay(250);
	}
}

void led_sdram_check()
{
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
	led_sdram_reset(); // G:*-*- R:----
	led_sdram_ready(); // G:*-*- R:-*-*
	led_sdram_busy(); // G:**** R:-*-*
	led_sdram_error(); // G:---- R:*-*-
	led_sdram_write_protected(); // G:**** R:----
	led_sdram_precharged(); // G:*-*- R:*-*-
}
/*

void PAW_Interface::load_buffer(const uint8_t numb)
{
	temp_adress = 0xD0000000 + adress_of_layer + numb * 256;
	HAL_SDRAM_Read_32b(&hsdram1, (uint32_t*) temp_adress, buffer, 256);
}

void PAW_Interface::save_buffer(const uint8_t numb)
{
	temp_adress = 0xD0000000 + adress_of_layer + numb * 256;
	HAL_SDRAM_Write_32b(&hsdram1, (uint32_t*) temp_adress, buffer, 256);
}
*/

#define PAW_LCD_X_SIZE 240
#define PAW_LCD_Y_SIZE 320
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_SPI5_Init();
  /* USER CODE BEGIN 2 */
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_SDRAM_Init();
	PAW_Buffer_init();
	GYRO_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
while(1){
//	demo();
//	demo1();
//	demo2();
//	demo3();
	demo4();
    /* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 432;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DMA2D Initialization Function
  * @param None
  * @retval None
  */
static void GYRO_Init(void)
{
	// w razie problemów z działaniem żyroskopu, przekopiowac ten kod do maina pod inicjalizacjami peryferiow
	// nie mam pojecia czemu czasem zyroskop dziala, a czasem nie, ale powyzdsza operacja przewaznie pomaga
	// a jak nie pomaga to jej kilkukrotne stosowanie i usuwanie juz pomaga
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	address_ctrl1 = 0x20;
	HAL_SPI_Transmit(&hspi5, &address_ctrl1, 1, 50);
	data_ctrl1 = 0x0f;
	HAL_SPI_Transmit(&hspi5, &data_ctrl1, 1, 50);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
}
	
static void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_RGB565;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_RGB565;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

}

/**
  * @brief LTDC Initialization Function
  * @param None
  * @retval None
  */
static void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 7;
  hltdc.Init.VerticalSync = 3;
  hltdc.Init.AccumulatedHBP = 14;
  hltdc.Init.AccumulatedVBP = 5;
  hltdc.Init.AccumulatedActiveW = 334;
  hltdc.Init.AccumulatedActiveH = 485;
  hltdc.Init.TotalWidth = 340;
  hltdc.Init.TotalHeigh = 487;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 320;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 240;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
  pLayerCfg.Alpha = 0;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = 0;
  pLayerCfg.ImageWidth = 0;
  pLayerCfg.ImageHeight = 0;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

/**
  * @brief SPI5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI5_Init(void)
{

  /* USER CODE BEGIN SPI5_Init 0 */

  /* USER CODE END SPI5_Init 0 */

  /* USER CODE BEGIN SPI5_Init 1 */

  /* USER CODE END SPI5_Init 1 */
  /* SPI5 parameter configuration*/
  hspi5.Instance = SPI5;
  hspi5.Init.Mode = SPI_MODE_MASTER;
  hspi5.Init.Direction = SPI_DIRECTION_2LINES;
  hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi5.Init.NSS = SPI_NSS_SOFT;
  hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi5.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI5_Init 2 */

  /* USER CODE END SPI5_Init 2 */

}

/** 
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma2_stream0
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Configure DMA request hdma_memtomem_dma2_stream0 on DMA2_Stream0 */
  hdma_memtomem_dma2_stream0.Instance = DMA2_Stream0;
  hdma_memtomem_dma2_stream0.Init.Channel = DMA_CHANNEL_0;
  hdma_memtomem_dma2_stream0.Init.Direction = DMA_MEMORY_TO_MEMORY;
  hdma_memtomem_dma2_stream0.Init.PeriphInc = DMA_PINC_ENABLE;
  hdma_memtomem_dma2_stream0.Init.MemInc = DMA_MINC_ENABLE;
  hdma_memtomem_dma2_stream0.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_memtomem_dma2_stream0.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_memtomem_dma2_stream0.Init.Mode = DMA_NORMAL;
  hdma_memtomem_dma2_stream0.Init.Priority = DMA_PRIORITY_MEDIUM;
  hdma_memtomem_dma2_stream0.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
  hdma_memtomem_dma2_stream0.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
  hdma_memtomem_dma2_stream0.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_memtomem_dma2_stream0.Init.PeriphBurst = DMA_PBURST_SINGLE;
  if (HAL_DMA_Init(&hdma_memtomem_dma2_stream0) != HAL_OK)
  {
    Error_Handler( );
  }

}
/* FMC initialization function */
static void MX_FMC_Init(void)
{
  FMC_SDRAM_TimingTypeDef SdramTiming;

  /** Perform the SDRAM1 memory initialization sequence
  */
  hsdram1.Instance = FMC_SDRAM_DEVICE;
  /* hsdram1.Init */
  hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_ENABLE;
  hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_2;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 16;
  SdramTiming.ExitSelfRefreshDelay = 16;
  SdramTiming.SelfRefreshTime = 16;
  SdramTiming.RowCycleDelay = 16;
  SdramTiming.WriteRecoveryTime = 16;
  SdramTiming.RPDelay = 16;
  SdramTiming.RCDDelay = 16;

  if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
  {
    Error_Handler( );
  }

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, NCS_MEMS_SPI_Pin|CSX_Pin|OTG_FS_PSO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ACP_RST_GPIO_Port, ACP_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, RDX_Pin|WRX_DCX_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LD3_Pin|LD4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : NCS_MEMS_SPI_Pin CSX_Pin OTG_FS_PSO_Pin */
  GPIO_InitStruct.Pin = NCS_MEMS_SPI_Pin|CSX_Pin|OTG_FS_PSO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MEMS_INT1_Pin MEMS_INT2_Pin TP_INT1_Pin */
  GPIO_InitStruct.Pin = MEMS_INT1_Pin|MEMS_INT2_Pin|TP_INT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ACP_RST_Pin */
  GPIO_InitStruct.Pin = ACP_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ACP_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OC_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TE_Pin */
  GPIO_InitStruct.Pin = TE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RDX_Pin WRX_DCX_Pin */
  GPIO_InitStruct.Pin = RDX_Pin|WRX_DCX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD4_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
