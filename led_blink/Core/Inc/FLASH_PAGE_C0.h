/*
 * FLASH_PAGE_C0.H
 *
 *  Created on: Jul 5, 2024
 *      Author: user
 */

#ifndef INC_FLASH_PAGE_C0_H_
#define INC_FLASH_PAGE_C0_H_

#include "stm32c0xx_hal.h"


uint32_t Flash_Write_Data (uint32_t StartPageAddress, uint32_t *Data, uint16_t numberofwords);

void Flash_Read_Data (uint32_t StartPageAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Convert_To_Str (uint32_t *Data, char *Buf);

void Flash_Write_NUM (uint32_t StartSectorAddress, float Num);

float Flash_Read_NUM (uint32_t StartSectorAddress);

void float2Bytes(uint8_t *ftoa_bytes_temp, float float_variable);


/********************  FLASH_Error_Codes   ***********************//*
HAL_FLASH_ERROR_NONE      0x00U  // No error
HAL_FLASH_ERROR_PROG      0x01U  // Programming error
HAL_FLASH_ERROR_WRP       0x02U  // Write protection error
HAL_FLASH_ERROR_OPTV      0x04U  // Option validity error
*/


#endif /* INC_FLASH_PAGE_C0_H_ */
