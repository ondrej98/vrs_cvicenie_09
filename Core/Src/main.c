/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fonts.h"
#include "display.h"
#include "i2c.h"
#include "../../compass/lis3mdltr.h"
#include "../../accelerometer/lsm6ds0.h"
#include "../../humidity/hts221.h"
#include "../../pressure/lps25hb.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern DisplayDigitData_ DisplayDigit_0;
extern DisplayDigitData_ DisplayDigit_1;
extern DisplayDigitData_ DisplayDigit_2;
extern DisplayDigitData_ DisplayDigit_3;
extern bool nextStringSequence;
extern uint8_t *aReceiveBuffer_read, end_of_read_flag;
extern volatile uint8_t ubReceiveIndex;
extern MetricsOption_ metOpt;
MetricsStruct metrics;
/*uint8_t temp = 0;
 float mag[3], acc[3];
 float humidity, temperature = -1.f;
 float pressure, altitude = 0;*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint8_t TEMPERATURE_STR_TEXT[] = "TEMP_";
const uint8_t TEMPERATURE_STR_PROT[] = "%04.1f";
const float TEMPERATURE_MIN = -99.9;
const float TEMPERATURE_MAX = 99.9;
const uint8_t HUMIDITY_STR_TEXT[] = "HUM_";
const uint8_t HUMIDITY_STR_PROT[] = "%02.0f";
const float HUMIDITY_MIN = 0.0;
const float HUMIDITY_MAX = 99.9;
const uint8_t PRESSURE_STR_TEXT[] = "BAR_";
const uint8_t PRESSURE_STR_PROT[] = "%07.2f";
const float PRESSURE_MIN = 260.0;
const float PRESSURE_MAX = 1259.9;
const uint8_t ALTITUDE_STR_TEXT[] = "ALT_";
const uint8_t ALTITUDE_STR_PROT[] = "%06.1f";
const float ALTITUDE_MIN = -1876.5;
const float ALTITUDE_MAX = 9999.9;
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */
	DisplayDigit_0.index = 0;
	DisplayDigit_0.chr = 0;
	DisplayDigit_1.index = 1;
	DisplayDigit_1.chr = 0;
	DisplayDigit_2.index = 2;
	DisplayDigit_2.chr = 0;
	DisplayDigit_3.index = 3;
	DisplayDigit_3.chr = 0;
	nextStringSequence = false;
	Direction_ direction = Direction_DownUp;
	end_of_read_flag = 0;
	ubReceiveIndex = 0;
	metOpt = MetricsOption_Temperature;
	metrics.temperature = -1;
	metrics.humidity = -1;
	metrics.pressure = -1;
	metrics.altitude = -1;
	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* System interrupt init*/

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_I2C1_Init();
	MX_TIM6_Init();
	MX_TIM7_Init();
	/* USER CODE BEGIN 2 */
	lsm6ds0_init();
	hts221_init();
	lps25hb_init();
	uint8_t index = 0;
	uint8_t string[STR_LEN] = { 0 };
	uint8_t lenString = STR_LEN;
	setMetricsOption(string, metOpt, metrics, &index);
	/*setString(string, TEMPERATURE_STR_TEXT, TEMPERATURE_STR_PROT, temperature,
	 TEMPERATURE_MIN, TEMPERATURE_MAX);*/
	lenString = strlen((const char*) string);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		if (nextStringSequence) {
			nextStringSequence = false;
			/*hts221_get_humidity(&humidity);
			 hts221_get_temperature(&temperature);
			 lps25hb_get_pressure(&pressure);
			 lps25hb_get_altitude(&altitude);*/
			hts221_get_temperature(&metrics.temperature);
			hts221_get_humidity(&metrics.humidity);
			lps25hb_get_pressure(&metrics.pressure);
			lps25hb_get_altitude(&metrics.altitude);
			/*setString(string, ALTITUDE_STR_TEXT, ALTITUDE_STR_PROT, altitude,
			 ALTITUDE_MIN, ALTITUDE_MAX);*/
			setMetricsOption(string, metOpt, metrics, &index);
			lenString = strlen((const char*) string);
			displayString(index, string, lenString);
			if (index + STR_DISP_LEN < lenString
					&& direction == Direction_DownUp) {
				index++;
			} else if (index + STR_DISP_LEN >= lenString
					&& direction == Direction_DownUp) {
				direction = Direction_UpDown;
			}
			if (index > 0 && direction == Direction_UpDown) {
				index--;
			} else if (index == 0 && direction == Direction_UpDown) {
				direction = Direction_DownUp;
			}
		}
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
	while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {
	}
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while (LL_RCC_HSI_IsReady() != 1) {

	}
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

	/* Wait till System clock is ready */
	while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI) {

	}
	LL_Init1msTick(8000000);
	LL_SetSystemCoreClock(8000000);
	LL_RCC_SetI2CClockSource(LL_RCC_I2C1_CLKSOURCE_HSI);
}

/* USER CODE BEGIN 4 */
void setMetricsOption(uint8_t *str, MetricsOption_ metricsOption,
		MetricsStruct metricsStruct, uint8_t *index) {
	switch (metricsOption) {
	default: //Unknown
		break;
	case MetricsOption_Temperature:
		setString(str, TEMPERATURE_STR_TEXT, TEMPERATURE_STR_PROT,
				metricsStruct.temperature, TEMPERATURE_MIN, TEMPERATURE_MAX);
		*index = 0;
		break;
	case MetricsOption_Humidity:
		setString(str, HUMIDITY_STR_TEXT, HUMIDITY_STR_PROT,
				metricsStruct.humidity, HUMIDITY_MIN, HUMIDITY_MAX);
		*index = 0;
		break;
	case MetricsOption_Pressure:
		setString(str, PRESSURE_STR_TEXT, PRESSURE_STR_PROT,
				metricsStruct.pressure, PRESSURE_MIN, PRESSURE_MAX);
		*index = 0;
		break;
	case MetricsOption_Altitude:
		setString(str, ALTITUDE_STR_TEXT, ALTITUDE_STR_PROT,
				metricsStruct.altitude, ALTITUDE_MIN, ALTITUDE_MAX);
		*index = 0;
		break;
	}
}
void setString(uint8_t *str, const uint8_t *strText, const uint8_t *strProt,
		float value, float minValue, float maxValue) {
	strcpy((char*) str, (const char*) strText);
	uint16_t len = strlen((const char*) str);
	if (value < minValue)
		value = minValue;
	else if (value > maxValue)
		value = maxValue;
	sprintf((char*) (str + len), (const char*) strProt, value);
}
uint8_t displayString(uint8_t index, uint8_t *str, uint8_t length) {
	uint8_t result = 0;
	if (index + STR_DISP_LEN <= length) {
		uint8_t dispStr[STR_DISP_LEN] = { 0 };
		memcpy(dispStr, str + index, STR_DISP_LEN);
		result = index + STR_DISP_LEN;
		DisplayDigit_0.chr = dispStr[0];
		DisplayDigit_1.chr = dispStr[1];
		DisplayDigit_2.chr = dispStr[2];
		DisplayDigit_3.chr = dispStr[3];

	}
	return result;
}
/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
