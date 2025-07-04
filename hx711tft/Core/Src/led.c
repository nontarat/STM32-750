/*
 * led.c
 *
 *  Created on: Apr 24, 2023
 *      Author: user
 */


#include "led.h"

//��ʼ��PB0,PB1Ϊ���.��ʹ���������ڵ�ʱ��
//LED IO��ʼ��
void LED_Init(void)
{


    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	//PB0��0
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	//PB1��1
}
