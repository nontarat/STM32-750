/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include "delay.h"
#include "sys.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "myiic.h"
#include "24cxx.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CALIBRATION_FACTOR 20
#define Diff 0
float weight=0.0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char counter_str[50];
 int32_t hx711_value;
static uint8_t GAIN;	//Gain for clock cycles.
static int32_t new_hx711_value;
/*
void delay_us1 (uint16_t us) //delay function
{
__HAL_TIM_SET_COUNTER(&htim1,0);  // setting the delay counter to 0.
while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // while loop till the counter reaches the delay given (us).
}
*/
void hx711_powerUp(void) //Power up function
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //writing to the pin and setting it to 0.
}
void hx711_setGain(uint8_t gain)  //the values should be 32, 64 or 128
{
	if(gain < 64) GAIN = 2; //32, channel B
	else if(gain < 128) GAIN = 3; //64, channel A
	else GAIN = 1; //128, channel A
}


void hx711_init(void) //initializes the hx711 module by calling 2 functions.
{
  hx711_setGain(128); //setting gain to 128, as this was our best result after trying with other gains.
	hx711_powerUp(); //power up the hx711 module.
}



int32_t hx711_get_value(void) //getting the weight from the module.
{
	uint32_t data = 0; //the data (weight) is firstly set to 0.
	uint8_t dout; // this is to show whether at this bit, if theres a number that should be recorded.
	int32_t filler; //to fill the rest of the 32 bits.
	int32_t ret_value; //final value to return after adding the filling and the data together.

	for (uint8_t i = 0; i < 24; i++) //read 24 bit data + set gain and start next conversion
	{

		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //set the clock pin to 1.
		delay_us(1); //delay
			dout = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3); //read from the dout pin in variable dout.
			data = data << 1; //shift the data by 1 to make sure we are in correct position depending on the counter.
			if (dout) //if this bit has an output (value of 1) .
			{
				data++; //it sets the data value at this position as 1 as well.
			}
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //set clock pin to 0.
		delay_us(1); //delay
	}

	for( int i = 0; i < GAIN; i ++ ) //this for loop is for the gain, to add more clock cycles based on the gain.
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET); //set clock pin to 1.
		delay_us(1); //delay
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); //set clock pin to 0.
		delay_us(1); //delay, here we are making a clock cycle.
	}

	if( data & 0x800000 ) //here we are checking if theres values in the 24 bits by anding.
		filler = 0xFF000000; //if there are values we add 1's to the last 8 bits which are needed as this is a 32-bit adc.
	else
		filler = 0x00000000; //however, if nothing is in the data we just add 0's.

	ret_value = filler + data; //the return value is the addition of the data with the filler to have the 32-bits.
	return ret_value; //returning the value to be printed.
}

uint8_t hx711_is_ready(void) //making sure that the HX711 module is ready
{
	return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET; //reading a value from it, the reseting it.
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

/* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI4_Init();
  MX_SPI2_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	delay_init(400);
	 LCD_Init();
	 IIC_Start();
	 IIC_Init();
	 AT24CXX_Init();
	 AT24CXX_Check();

	   hx711_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if( hx711_is_ready()) //if the HX711 module is ready.
	 	  {
	 		  hx711_value = hx711_get_value(); //we store the value coming from the get value function.

	 	      sprintf(counter_str, "Weight : %d kg \r\n",(((hx711_value)/12300)-15)*2);
	 	    //CDC_Transmit_FS((uint8_t*)counter_str, strlen(counter_str));
	 	    //Gui_StrCenter(0, 30, RED, BLACK, counter_str, 16	, 1);
	 	  }
	 	  else{
	 		  	sprintf(counter_str,"Error: HX711 \n\r"); //However, if the HX711 module dosent read any value, this means there is a connection error.
	 	   // CDC_Transmit_FS((uint8_t*)counter_str, strlen(counter_str));
	 	  }

	  	//  main_test();
	    Gui_StrCenter(0, 50, RED, BLACK, counter_str, 16	, 1);
	 	    HAL_Delay(100); //creating a delay.
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CKPER;
  PeriphClkInitStruct.CkperClockSelection = RCC_CLKPSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
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
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
