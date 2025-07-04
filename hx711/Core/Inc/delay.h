/*
 * delay.h
 *
 *  Created on: Apr 22, 2023
 *      Author: user
 */

#ifndef INC_DELAY_H_
#define INC_DELAY_H_

#include "sys.h"

void delay_init(u16 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#endif /* INC_DELAY_H_ */
