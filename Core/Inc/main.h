/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f3xx_ll_i2c.h"
#include "stm32f3xx_ll_rcc.h"
#include "stm32f3xx_ll_bus.h"
#include "stm32f3xx_ll_system.h"
#include "stm32f3xx_ll_exti.h"
#include "stm32f3xx_ll_cortex.h"
#include "stm32f3xx_ll_utils.h"
#include "stm32f3xx_ll_pwr.h"
#include "stm32f3xx_ll_dma.h"
#include "stm32f3xx_ll_tim.h"
#include "stm32f3xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef enum {
	Direction_DownUp, Direction_UpDown
} Direction_;
typedef enum {
	MetricsOption_Temperature = 0,
	MetricsOption_Humidity,
	MetricsOption_Pressure,
	MetricsOption_Altitude = 3,
} MetricsOption_;
typedef struct{
	float temperature;
	float humidity;
	float pressure;
	float altitude;
} MetricsStruct;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define STR_DISP_LEN 4
#define STR_LEN 20
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/**
 *  Function checks if the button was pressed or EXTI detection was false - positive.
 *  @input_param_1 - PORT: GPIO port connected to button.
 *  @input_param_2 - PIN: GPIO pin connected to button.
 *  @input_param_3 - edge: EXTI trigger edge. Defines what is the input GPIO idle state after the button is pressed.
 *  					   TRIGGER_RISE - input is expected to be "1" after EXTI was triggered.
 *  					   TRIGGER_FALL - input is expected to be "0" after EXTI was triggered.
 *  @input_param_4 - samples_window: How many samples are checked (input port is read) after EXTI is triggered.
 *  @input_param_5 - samples_required: How many samples in row are required to be in the idle state.
 */
uint8_t checkButtonState(GPIO_TypeDef* PORT, uint8_t PIN, uint8_t edge, uint8_t samples_window, uint8_t samples_required);
void setMetricsOption(uint8_t *str, MetricsOption_ metricsOption, MetricsStruct metricsStruct);
void setString(uint8_t *str, const uint8_t *strText, const uint8_t *strProt,
		float value, float minValue, float maxValue);
uint8_t displayString(uint8_t index, uint8_t *str, uint8_t length);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MCO_Pin LL_GPIO_PIN_0
#define MCO_GPIO_Port GPIOF
#define S_B_Pin LL_GPIO_PIN_0
#define S_B_GPIO_Port GPIOA
#define S_A_Pin LL_GPIO_PIN_1
#define S_A_GPIO_Port GPIOA
#define D_3_Pin LL_GPIO_PIN_2
#define D_3_GPIO_Port GPIOA
#define S_F_Pin LL_GPIO_PIN_3
#define S_F_GPIO_Port GPIOA
#define D_1_Pin LL_GPIO_PIN_4
#define D_1_GPIO_Port GPIOA
#define D_T_Pin LL_GPIO_PIN_7
#define D_T_GPIO_Port GPIOA
#define D_0_Pin LL_GPIO_PIN_0
#define D_0_GPIO_Port GPIOB
#define S_DP_Pin LL_GPIO_PIN_1
#define S_DP_GPIO_Port GPIOB
#define S_C_Pin LL_GPIO_PIN_8
#define S_C_GPIO_Port GPIOA
#define S_E_Pin LL_GPIO_PIN_11
#define S_E_GPIO_Port GPIOA
#define D_2_Pin LL_GPIO_PIN_12
#define D_2_GPIO_Port GPIOA
#define SWDIO_Pin LL_GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin LL_GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define VCP_RX_Pin LL_GPIO_PIN_15
#define VCP_RX_GPIO_Port GPIOA
#define TLACIDLO_Pin LL_GPIO_PIN_3
#define TLACIDLO_GPIO_Port GPIOB
#define TLACIDLO_EXTI_IRQn EXTI3_IRQn
#define S_G_Pin LL_GPIO_PIN_4
#define S_G_GPIO_Port GPIOB
#define S_D_Pin LL_GPIO_PIN_5
#define S_D_GPIO_Port GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0         ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority,
                                                                 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1         ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority,
                                                                 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2         ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority,
                                                                 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3         ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority,
                                                                 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4         ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority,
                                                                 0 bit  for subpriority */
#endif
/* USER CODE BEGIN Private defines */
MetricsOption_ metOpt;
uint8_t switch_state;
#define		TRIGGER_RISE					0
#define		TRIGGER_FALL					1
#define		BUTTON_EXTI_TRIGGER				TRIGGER_FALL
#define		BUTTON_EXTI_SAMPLES_WINDOW		30
#define		BUTTON_EXTI_SAMPLES_REQUIRED	20
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
