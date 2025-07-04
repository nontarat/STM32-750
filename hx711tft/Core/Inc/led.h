/*
 * led.h
 *
 *  Created on: Apr 24, 2023
 *      Author: user
 */

#ifndef INC_LED_H_
#define INC_LED_H_

#include "sys.h"

//LED
#define LED0(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET))
#define LED0_Toggle (HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1)) //LED0�����ƽ��ת
#define LED1(n)		(n?HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET))
#define LED1_Toggle (HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0)) //LED1�����ƽ��ת

void LED_Init(void); //LED��ʼ������

#endif /* INC_LED_H_ */
