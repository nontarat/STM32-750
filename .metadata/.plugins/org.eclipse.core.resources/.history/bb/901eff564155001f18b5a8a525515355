/*
 * lcd.h
 *
 *  Created on: Jul 31, 2024
 *      Author: user
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32h7xx_hal.h"

#define RS_Pin GPIO_PIN_0
#define EN_Pin GPIO_PIN_1
#define D4_Pin GPIO_PIN_2
#define D5_Pin GPIO_PIN_3
#define D6_Pin GPIO_PIN_4
#define D7_Pin GPIO_PIN_5
#define LCD_Port GPIOA

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_send_to_lcd(char data, int rs);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_clear(void);
void lcd_scroll_left(char *str, uint16_t delay);
void lcd_appear_one_by_one(char *str, uint16_t delay);
void lcd_scroll_right(char *str, uint16_t delay);
void lcd_count_numbers(void);


#endif /* INC_LCD_H_ */
