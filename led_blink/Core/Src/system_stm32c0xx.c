/**
  ******************************************************************************
  * @file    system_stm32c0xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32c0xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32c0xx_system
  * @{
  */

/** @addtogroup STM32C0xx_System_Private_Includes
  * @{
  */

#include "stm32c0xx.h"

#if !defined  (HSE_VALUE)
#define HSE_VALUE    (48000000UL)    /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE  (48000000UL)   /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (LSI_VALUE)
 #define LSI_VALUE   (32000UL)     /*!< Value of LSI in Hz*/
#endif /* LSI_VALUE */

#if !defined  (LSE_VALUE)
  #define LSE_VALUE  (32768UL)      /*!< Value of LSE in Hz*/
#endif /* LSE_VALUE */

#if defined(RCC_HSI48_SUPPORT)
#if !defined  (HSI48_VALUE)
#define HSI48_VALUE  48000000U  /*!< Value of the HSI48 oscillator in Hz */
#endif /* HSI48_VALUE */
#endif /* RCC_HSI48_SUPPORT */

/**
  * @}
  */

/** @addtogroup STM32C0xx_System_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32C0xx_System_Private_Defines
  * @{
  */

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
//#define VECT_TAB_SRAM 
#define VECT_TAB_OFFSET  0x0U /*!< Vector Table base offset field.
                                   This value must be a multiple of 0x100. */
/******************************************************************************/
/**
  * @}
  */

/** @addtogroup STM32C0xx_System_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32C0xx_System_Private_Variables
  * @{
  */
  /* The SystemCoreClock variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetHCLKFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
  uint32_t SystemCoreClock = 12000000UL;

  const uint32_t AHBPrescTable[16UL] = {0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL, 6UL, 7UL, 8UL, 9UL};
  const uint32_t APBPrescTable[8UL] =  {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};

/**
  * @}
  */

/** @addtogroup STM32C0xx_System_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @addtogroup STM32C0xx_System_Private_Functions
  * @{
  */

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
  
  /* Configure the Vector Table location add offset address ------------------*/
#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH */
#endif
 }

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**) / HSI division factor
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is LSI, SystemCoreClock will contain the LSI_VALUE
  *
  *           - If SYSCLK source is LSE, SystemCoreClock will contain the LSE_VALUE
  *
  *         (**) HSI_VALUE is a constant defined in stm32c0xx_hal_conf.h file (default value
  *              48 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32c0xx_hal_conf.h file (default value
  *              48 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
  uint32_t tmp;
  uint32_t hsidiv;
  uint32_t sysdiv;
#if defined(RCC_CR_SYSDIV)
  sysdiv = (uint32_t)(((RCC->CR & RCC_CR_SYSDIV) >> RCC_CR_SYSDIV_Pos) + 1U);
#else
  sysdiv = 1U;
#endif /* RCC_CR_SYSDIV */

  /* Get SYSCLK source -------------------------------------------------------*/
  switch (RCC->CFGR & RCC_CFGR_SWS)
  {
    case RCC_CFGR_SWS_0:                /* HSE used as system clock */
      SystemCoreClock = (HSE_VALUE / sysdiv);
      break;

#if defined(RCC_HSI48_SUPPORT)
    case RCC_CFGR_SW_1:                 /* HSI48 used as system clock */
      SystemCoreClock = (HSI48_VALUE / sysdiv);
      break;
#endif /* RCC_HSI48_SUPPORT */

    case (RCC_CFGR_SWS_1 | RCC_CFGR_SWS_0):  /* LSI used as system clock */
      SystemCoreClock = (LSI_VALUE / sysdiv);
      break;

    case RCC_CFGR_SWS_2:                /* LSE used as system clock */
      SystemCoreClock = (LSE_VALUE / sysdiv);
      break;

    case 0x00000000U:                   /* HSI used as system clock */
    default:                            /* HSI used as system clock */
      hsidiv = (1UL << ((READ_BIT(RCC->CR, RCC_CR_HSIDIV))>> RCC_CR_HSIDIV_Pos));
      SystemCoreClock = ((HSI_VALUE / sysdiv) / hsidiv);
      break;
  }
  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> RCC_CFGR_HPRE_Pos)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
