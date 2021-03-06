/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "epd1in54.h"
#include "epdif.h"
#include "epdpaint.h"
#include "startimage.h"
#include "imagedata.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"


#define COLORED      0
#define UNCOLORED    1
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
int dev1, dev2, dev3, dev4=0;
void DisplayString(Paint* paint,int nr,const char* text,EPD* epd, const unsigned char* image_buffer);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	 unsigned char frame_buffer[EPD_WIDTH * EPD_HEIGHT / 8];

	  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
	  unsigned long time_start_ms;
	  unsigned long time_now_s;


  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_SPI2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */


  EPD epd;
  EPD_Init(&epd, lut_full_update);

  Paint paint;
  Paint_Init(&paint, frame_buffer, epd.width, epd.height);
  Paint_Clear(&paint, UNCOLORED);

  /* For simplicity, the arguments are explicit numerical coordinates */
  /* Write strings to the buffer */
//  Paint_DrawFilledRectangle(&paint, 0, 6, 200, 26, COLORED);
//  Paint_DrawStringAt(&paint, 28, 10, "InteliHouse", &Font16, UNCOLORED);
  //Paint_DrawStringAt(&paint, 30, 30, "1.Dioda ON/OFF ", &Font16, COLORED);
  //Paint_DrawStringAt(&paint, 30, 30, "2.Muzyka ON/OFF ", &Font16, COLORED);
 // Paint_DrawStringAt(&paint, 30, 30, "1.Zapal diode ", &Font16, COLORED);



//  /* Draw something to the frame buffer */
//  Paint_DrawRectangle(&paint, 10, 60, 50, 110, COLORED);
//  Paint_DrawLine(&paint, 10, 60, 50, 110, COLORED);
//  Paint_DrawLine(&paint, 50, 60, 10, 110, COLORED);
//  Paint_DrawCircle(&paint, 120, 80, 30, COLORED);
//  Paint_DrawFilledRectangle(&paint, 10, 130, 50, 180, COLORED);
//  Paint_DrawFilledCircle(&paint, 120, 150, 30, COLORED);
//
//  /* Display the frame_buffer */
//  EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
//  EPD_DisplayFrame(&epd);
// // EPD_DelayMs(&epd, 20000);
//  EPD_DelayMs(&epd, 200);

  EPD_Init(&epd, lut_partial_update);
  /**
    *  there are 2 memory areas embedded in the e-paper display
    *  and once the display is refreshed, the memory area will be auto-toggled,
    *  i.e. the next action of SetFrameMemory will set the other memory area
    *  therefore you have to set the frame memory and refresh the display twice.
    */

  //wyswietlanie ekranu startowego
  EPD_SetFrameMemory(&epd, START_IMAGE, 0, 0, epd.width, epd.height);

  EPD_DisplayFrame(&epd);
  EPD_SetFrameMemory(&epd, START_IMAGE, 0, 0, epd.width, epd.height);
  EPD_DisplayFrame(&epd);
  EPD_DelayMs(&epd, 2000);
  time_start_ms = HAL_GetTick();

  /* For simplicity, the arguments are explicit numerical coordinates */
  /* Write strings to the buffer */
  Paint_DrawFilledRectangle(&paint, 0, 6, 200, 26, COLORED);
  Paint_DrawStringAt(&paint, 28, 10, "InteliHouse", &Font16, UNCOLORED);
  Paint_DrawStringAt(&paint, 20, 30, "Wybierz przycisk ", &Font16, COLORED);


Paint_DrawCircle(&paint, 50, 80, 30, COLORED);

Paint_DrawCircle(&paint, 150, 80, 30, COLORED);
			 Paint_DrawCircle(&paint, 50, 150, 30, COLORED);
			  Paint_DrawCircle(&paint, 150, 150, 30, COLORED);

  //wyswietlanie ekranu glownego
  /* Display the frame_buffer */
  EPD_SetFrameMemory(&epd, frame_buffer, 0, 0, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
  EPD_DisplayFrame(&epd);

  EPD_DelayMs(&epd, 200);



/*//Funkcje do komunikacji przez UART z ESP88266
  uint8_t buffer[10];
  HAL_UART_Transmit(&huart2,(uint8_t*) "witam", sizeof("witam"), 1000);
  HAL_UART_Receive(&huart2, buffer, 10, 1000);
*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  while (1)
  {
//PB4 PB5 PB7 PB8 input
  /* USER CODE END WHILE */
//
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)&&(dev1==0)){
		 //wlaczanie urzadzenia 1
		 //HAL_GPIO_TogglePin(LD3_GPIO_Port,GPIO_PIN_13);
		 HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_SET);
		 dev1=1;
		 DisplayString(&paint,11,"Device 1 ON",&epd,frame_buffer);

	 }
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)&&(dev1==1)){
		 //wylaczanie urzadzenia 1
	 		 HAL_GPIO_WritePin(LD3_GPIO_Port,LD3_Pin,GPIO_PIN_RESET);
	 		 dev1=0;
	 		 DisplayString(&paint,10,"Device 1 OFF",&epd,frame_buffer);

	 	 }
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)&&(dev2==0)){
		 //wlaczanie urzadzenia 2
	 	 		 HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,GPIO_PIN_SET);
	 	 		 dev2=1;
	 	 		 DisplayString(&paint,21,"Device 2 ON",&epd,frame_buffer);

	 	 	 }
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)&&(dev2==1)){
		 //wylaczanie urzadzenia 2
	 	 		 HAL_GPIO_WritePin(LD4_GPIO_Port,LD4_Pin,GPIO_PIN_RESET);
	 	 		 dev2=0;
	 	 		 DisplayString(&paint,20,"Device 2 OFF",&epd,frame_buffer);

	 	 	 }
	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)&&(dev3==0)){
		 //wlaczanie urzadzenia 3
	 	 	 		 HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_SET);
	 	 	 		 dev3=1;
	 	 	 		 DisplayString(&paint,31,"Device 3 ON",&epd,frame_buffer);

	 	 	 	 }
	 	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)&&(dev3==1)){
	 		 //wylaczanie urzadzenia 3
	 	 	 		 HAL_GPIO_WritePin(LD5_GPIO_Port,LD5_Pin,GPIO_PIN_RESET);
	 	 	 		 dev3=0;
	 	 	 		 DisplayString(&paint,30,"Device 3 OFF",&epd,frame_buffer);
	 	 	 	 }
	 	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)&&(dev4==0)){
	 		 //wlaczanie urzadzenia 4
	 		 	 		 //HAL_GPIO_TogglePin(LD3_GPIO_Port,GPIO_PIN_13);
	 		 	 		 HAL_GPIO_WritePin(LD6_GPIO_Port,LD6_Pin,GPIO_PIN_SET);
	 		 	 		 dev4=1;
	 		 	 		 DisplayString(&paint,41,"Device 4 ON",&epd,frame_buffer);

	 		 	 	 }
	 		 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8)&&(dev4==1)){
	 			 //wylaczanie urzadzenia 4
	 		 	 		 //HAL_GPIO_TogglePin(LD3_GPIO_Port,GPIO_PIN_13);
	 		 	 		 HAL_GPIO_WritePin(LD6_GPIO_Port,LD6_Pin,GPIO_PIN_RESET);
	 		 	 		 dev4=0;
	 		 	 		 DisplayString(&paint,40,"Device 4 OFF",&epd,frame_buffer);

	 		 	 	 }

  /* USER CODE BEGIN 3 */
//	  time_now_s = (HAL_GetTick() - time_start_ms) / 1000;
//	     time_string[0] = time_now_s / 60 / 10 + '0';
//	     time_string[1] = time_now_s / 60 % 10 + '0';
//	     time_string[3] = time_now_s % 60 / 10 + '0';
//	     time_string[4] = time_now_s % 60 % 10 + '0';
//
//	     Paint_SetWidth(&paint, 32);
//	     Paint_SetHeight(&paint, 96);
//	     Paint_SetRotate(&paint, ROTATE_270);
//
//	     Paint_Clear(&paint, UNCOLORED);
//	     Paint_DrawStringAt(&paint, 0, 4, time_string, &Font24, COLORED);
//	   //  EPD_SetFrameMemory(&epd, frame_buffer, 80, 72, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
//		 //   EPD_SetFrameMemory(&epd, frame_buffer, 10, 20, Paint_GetWidth(&paint), Paint_GetHeight(&paint));
//
//
//	     EPD_DisplayFrame(&epd);
//
//	     EPD_DelayMs(&epd, 500);
 // }
  /* USER CODE END 3 */

}
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void DisplayString(Paint* paint,int nr,const char* text,EPD* epd, const unsigned char* image_buffer){
	Paint_Clear(paint, UNCOLORED);
			 Paint_DrawFilledRectangle(paint, 0, 6, 200, 26, COLORED);
			  Paint_DrawStringAt(paint, 28, 10, "InteliHouse", &Font16, UNCOLORED);
			 Paint_DrawStringAt(paint, 30, 30, text, &Font16, COLORED);
			 /* Draw something to the frame buffer */
			 // Paint_DrawRectangle(paint, 10, 60, 50, 110, COLORED);
			// Paint_DrawRectangle(paint, 10, 60, 50, 110, COLORED);
			 // Paint_DrawLine(paint, 10, 60, 50, 110, COLORED);
			 // Paint_DrawLine(paint, 50, 60, 10, 110, COLORED);
//			switch(nr){
//			case 11:  Paint_DrawFilledCircle(paint, 50, 80, 30, COLORED);
//			break;
//			case 10:
//				break;
//			case 21:
//				break;
//			case 20:
//				break;
//			case 31:
//				break;
//			case 30:
//				break;
//			case 41:
//				break;
//			case 40:
//			break;
//
//
//			}

			 if(dev1==0)  Paint_DrawCircle(paint, 50, 80, 30, COLORED);
			 else Paint_DrawFilledCircle(paint, 50, 80, 30, COLORED);
			 if(dev2==0)  Paint_DrawCircle(paint, 150, 80, 30, COLORED);
			else Paint_DrawFilledCircle(paint, 150, 80, 30, COLORED);
			 if(dev3==0)  Paint_DrawCircle(paint, 50, 150, 30, COLORED);
			 else Paint_DrawFilledCircle(paint, 50, 150, 30, COLORED);
			 if(dev4==0) Paint_DrawCircle(paint, 150, 150, 30, COLORED);
			 else Paint_DrawFilledCircle(paint, 150, 150, 30, COLORED);





			 // Paint_DrawFilledRectangle(paint, 10, 130, 50, 180, COLORED);
			 // Paint_DrawFilledCircle(paint, 120, 150, 30, COLORED);

			  //wyswietlanie ekranu glownego
			  /* Display the frame_buffer */
			  EPD_SetFrameMemory(epd, image_buffer, 0, 0, Paint_GetWidth(paint), Paint_GetHeight(paint));
			  EPD_DisplayFrame(epd);
			  EPD_DelayMs(epd, 500);

}
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI2 init function */
static void MX_SPI2_Init(void)
{

  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PC3   ------> I2S2_SD
     PA4   ------> I2S3_WS
     PA5   ------> SPI1_SCK
     PA6   ------> SPI1_MISO
     PA7   ------> SPI1_MOSI
     PB10   ------> I2S2_CK
     PC7   ------> I2S3_MCK
     PA9   ------> USB_OTG_FS_VBUS
     PA10   ------> USB_OTG_FS_ID
     PA11   ------> USB_OTG_FS_DM
     PA12   ------> USB_OTG_FS_DP
     PC10   ------> I2S3_CK
     PC12   ------> I2S3_SD
     PB6   ------> I2C1_SCL
     PB9   ------> I2C1_SDA
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|DC_Pin|RST_Pin|SPI_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin 
                          |Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CS_I2C_SPI_Pin DC_Pin RST_Pin SPI_CS_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|DC_Pin|RST_Pin|SPI_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : I2S3_WS_Pin */
  GPIO_InitStruct.Pin = I2S3_WS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(I2S3_WS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPI1_SCK_Pin SPI1_MISO_Pin SPI1_MOSI_Pin */
  GPIO_InitStruct.Pin = SPI1_SCK_Pin|SPI1_MISO_Pin|SPI1_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BOOT1_Pin PB4 PB5 PB7 
                           PB8 */
  GPIO_InitStruct.Pin = BOOT1_Pin|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7 
                          |GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BUSY_Pin */
  GPIO_InitStruct.Pin = BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BUSY_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : INFRARED_Pin */
  GPIO_InitStruct.Pin = INFRARED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INFRARED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD4_Pin LD3_Pin LD5_Pin LD6_Pin 
                           Audio_RST_Pin */
  GPIO_InitStruct.Pin = LD4_Pin|LD3_Pin|LD5_Pin|LD6_Pin 
                          |Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : I2S3_MCK_Pin I2S3_SCK_Pin I2S3_SD_Pin */
  GPIO_InitStruct.Pin = I2S3_MCK_Pin|I2S3_SCK_Pin|I2S3_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(VBUS_FS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : OTG_FS_ID_Pin OTG_FS_DM_Pin OTG_FS_DP_Pin */
  GPIO_InitStruct.Pin = OTG_FS_ID_Pin|OTG_FS_DM_Pin|OTG_FS_DP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
