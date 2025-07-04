/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#include "sys.h"
/* USER CODE END Includes */

extern SPI_HandleTypeDef hspi2;

extern SPI_HandleTypeDef hspi4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_SPI2_Init(void);
void MX_SPI4_Init(void);

/* USER CODE BEGIN Prototypes */
#define SPI_MOSI(n)  (n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,GPIO_PIN_RESET))
#define SPI_SCLK(n)  (n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,GPIO_PIN_RESET))
#define SPI_MISO  HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)

#define	SPI_MOSI_SET  	SPI_MOSI(1) //LCD_CTRL->BSRR=SPI_MOSI
#define	SPI_SCLK_SET  	SPI_SCLK(1) //LCD_CTRL->BSRR=SPI_SCLK

#define	SPI_MOSI_CLR  	SPI_MOSI(0) //LCD_CTRL->BRR=SPI_MOSI
#define	SPI_SCLK_CLR  	SPI_SCLK(0) //LCD_CTRL->BRR=SPI_SCLK

void  SPIv_WriteData(u8 Data);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

