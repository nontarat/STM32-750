/*
 * lcd.c
 *
 *  Created on: Jul 31, 2024
 *      Author: user
 */

#include "lcd.h"
#include "string.h"
#include "stdio.h"

// Initialization function for LCD
void lcd_init(void) {
    HAL_Delay(50);             // Initial delay for LCD power up
    lcd_send_cmd(0x30);        // Wake up command
    HAL_Delay(5);
    lcd_send_cmd(0x30);        // Wake up command
    HAL_Delay(1);
    lcd_send_cmd(0x30);        // Wake up command
    HAL_Delay(10);
    lcd_send_cmd(0x20);        // Set 4-bit mode
    HAL_Delay(10);
    lcd_send_cmd(0x28);        // Function set: 4-bit mode, 2 lines, 5x8 dots
    HAL_Delay(1);
    lcd_send_cmd(0x0C);        // Display on, cursor off, blink off
    HAL_Delay(1);
    lcd_send_cmd(0x01);        // Clear display
    HAL_Delay(2);
    lcd_send_cmd(0x06);        // Entry mode set: increment cursor, no shift
    HAL_Delay(1);
}

// Send command to LCD
void lcd_send_cmd(char cmd) {
    lcd_send_to_lcd(cmd, 0);
}

// Send data to LCD
void lcd_send_data(char data) {
    lcd_send_to_lcd(data, 1);
}

// Send a string to the LCD
void lcd_send_string(char *str) {
    while (*str) lcd_send_data(*str++);
}

// Low level function to send data/command to LCD
void lcd_send_to_lcd(char data, int rs) {
    // Set RS pin
    HAL_GPIO_WritePin(LCD_Port, RS_Pin, rs);

    // Send higher nibble
    HAL_GPIO_WritePin(LCD_Port, EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_Port, D4_Pin, (data >> 4) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, D5_Pin, (data >> 5) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, D6_Pin, (data >> 6) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, D7_Pin, (data >> 7) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, EN_Pin, GPIO_PIN_RESET);

    // Small delay to ensure data is properly written
   // HAL_Delay(1);

    // Send lower nibble
    HAL_GPIO_WritePin(LCD_Port, EN_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_Port, D4_Pin, data & 0x01);
    HAL_GPIO_WritePin(LCD_Port, D5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, D6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, D7_Pin, (data >> 3) & 0x01);
    HAL_GPIO_WritePin(LCD_Port, EN_Pin, GPIO_PIN_RESET);

    // Small delay to ensure data is properly written
    HAL_Delay(1);
}

// Set cursor position on LCD
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t address;
    switch(row) {
        case 0:
            address = 0x00 + col;
            break;
        case 1:
            address = 0x40 + col;
            break;
        default:
            address = 0x00 + col;
            break;
    }
    lcd_send_cmd(0x80 | address);
}

// Clear LCD display
void lcd_clear(void) {
    lcd_send_cmd(0x01);
    HAL_Delay(2); // Clear display command needs a longer delay
}
void lcd_scroll_left(char *str, uint16_t delay) {
    char buffer[17]; // Buffer ขนาด 16 ตัวอักษร + 1 สำหรับ null terminator
    size_t len = strlen(str);
    size_t scroll_len = len + 16; // ความยาวทั้งหมดที่ต้องการเลื่อน

    for (size_t i = 0; i < scroll_len; i++) {
        memset(buffer, ' ', 16); // เติมช่องว่างใน buffer
        buffer[16] = '\0'; // ใส่ null terminator

        // คัดลอกข้อความลงบัฟเฟอร์
        if (i < len) {
            strncpy(buffer, str + i, 16);
        } else {
            // กรณีที่ข้อความไม่เต็มบัฟเฟอร์
            strncpy(buffer, str + i, 16);
        }

        lcd_set_cursor(0, 0);
        lcd_send_string(buffer);
        HAL_Delay(delay);
    }
}


void lcd_scroll_right(char *str, uint16_t delay) {
    char buffer[17]; // Buffer ขนาด 16 ตัวอักษร + 1 สำหรับ null terminator
    size_t len = strlen(str);
    size_t scroll_len = len + 16; // ความยาวทั้งหมดที่ต้องการเลื่อน

    for (int i = 0; i < scroll_len; i++) {
        memset(buffer, ' ', 16); // เติมช่องว่างใน buffer
        buffer[16] = '\0'; // ใส่ null terminator

        // คัดลอกข้อความลงบัฟเฟอร์
        if (i < 16) {
            strncpy(buffer + 16 - i, str, i);
        } else {
            strncpy(buffer, str + (i - 16), 16);
        }

        lcd_set_cursor(0, 0);
        lcd_send_string(buffer);
        HAL_Delay(delay);
    }
}



void lcd_appear_one_by_one(char *str, uint16_t delay) {
	 while (*str) {
	        lcd_send_data(*str++);
	        HAL_Delay(delay);
	    }
}
