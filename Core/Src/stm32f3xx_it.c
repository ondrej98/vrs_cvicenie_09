/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32f3xx_it.c
 * @brief   Interrupt Service Routines.
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
#include "stm32f3xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "display.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern bool nextStringSequence;
extern uint8_t *aReceiveBuffer_read, end_of_read_flag;
extern volatile uint8_t ubReceiveIndex;
extern MetricsOption_ metOpt;
extern uint8_t switch_state;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
 * @brief This function handles Non maskable interrupt.
 */
void NMI_Handler(void) {
	/* USER CODE BEGIN NonMaskableInt_IRQn 0 */

	/* USER CODE END NonMaskableInt_IRQn 0 */
	/* USER CODE BEGIN NonMaskableInt_IRQn 1 */
	while (1) {
	}
	/* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
 * @brief This function handles Hard fault interrupt.
 */
void HardFault_Handler(void) {
	/* USER CODE BEGIN HardFault_IRQn 0 */

	/* USER CODE END HardFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_HardFault_IRQn 0 */
		/* USER CODE END W1_HardFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Memory management fault.
 */
void MemManage_Handler(void) {
	/* USER CODE BEGIN MemoryManagement_IRQn 0 */

	/* USER CODE END MemoryManagement_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
		/* USER CODE END W1_MemoryManagement_IRQn 0 */
	}
}

/**
 * @brief This function handles Pre-fetch fault, memory access fault.
 */
void BusFault_Handler(void) {
	/* USER CODE BEGIN BusFault_IRQn 0 */

	/* USER CODE END BusFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_BusFault_IRQn 0 */
		/* USER CODE END W1_BusFault_IRQn 0 */
	}
}

/**
 * @brief This function handles Undefined instruction or illegal state.
 */
void UsageFault_Handler(void) {
	/* USER CODE BEGIN UsageFault_IRQn 0 */

	/* USER CODE END UsageFault_IRQn 0 */
	while (1) {
		/* USER CODE BEGIN W1_UsageFault_IRQn 0 */
		/* USER CODE END W1_UsageFault_IRQn 0 */
	}
}

/**
 * @brief This function handles System service call via SWI instruction.
 */
void SVC_Handler(void) {
	/* USER CODE BEGIN SVCall_IRQn 0 */

	/* USER CODE END SVCall_IRQn 0 */
	/* USER CODE BEGIN SVCall_IRQn 1 */

	/* USER CODE END SVCall_IRQn 1 */
}

/**
 * @brief This function handles Debug monitor.
 */
void DebugMon_Handler(void) {
	/* USER CODE BEGIN DebugMonitor_IRQn 0 */

	/* USER CODE END DebugMonitor_IRQn 0 */
	/* USER CODE BEGIN DebugMonitor_IRQn 1 */

	/* USER CODE END DebugMonitor_IRQn 1 */
}

/**
 * @brief This function handles Pendable request for system service.
 */
void PendSV_Handler(void) {
	/* USER CODE BEGIN PendSV_IRQn 0 */

	/* USER CODE END PendSV_IRQn 0 */
	/* USER CODE BEGIN PendSV_IRQn 1 */

	/* USER CODE END PendSV_IRQn 1 */
}

/**
 * @brief This function handles System tick timer.
 */
void SysTick_Handler(void) {
	/* USER CODE BEGIN SysTick_IRQn 0 */

	/* USER CODE END SysTick_IRQn 0 */

	/* USER CODE BEGIN SysTick_IRQn 1 */

	/* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
 * @brief This function handles EXTI line 3 interrupt.
 */
void EXTI3_IRQHandler(void) {
	/* USER CODE BEGIN EXTI3_IRQn 0 */

	/* USER CODE END EXTI3_IRQn 0 */
	if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_3) != RESET) {
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_3);
		/* USER CODE BEGIN LL_EXTI_LINE_3 */
		if (checkButtonState(TLACIDLO_GPIO_Port, TLACIDLO_Pin, BUTTON_EXTI_TRIGGER,
			BUTTON_EXTI_SAMPLES_WINDOW, BUTTON_EXTI_SAMPLES_REQUIRED) && switch_state == 0) {
				switch_state = 1;
			}
		/* USER CODE END LL_EXTI_LINE_3 */
	}
	/* USER CODE BEGIN EXTI3_IRQn 1 */

	/* USER CODE END EXTI3_IRQn 1 */
}

/**
 * @brief This function handles I2C1 event global interrupt / I2C1 wake-up interrupt through EXT line 23.
 */
void I2C1_EV_IRQHandler(void) {
	/* USER CODE BEGIN I2C1_EV_IRQn 0 */
	if (LL_I2C_IsActiveFlag_RXNE(I2C1)) {
		/* Call function Master Reception Callback */
		aReceiveBuffer_read[ubReceiveIndex++] = LL_I2C_ReceiveData8(I2C1);
		(ubReceiveIndex > 19) ? ubReceiveIndex = 0 : ubReceiveIndex;
		end_of_read_flag = 0;
	}
	/* USER CODE END I2C1_EV_IRQn 0 */

	/* USER CODE BEGIN I2C1_EV_IRQn 1 */

	/* USER CODE END I2C1_EV_IRQn 1 */
}

/**
 * @brief This function handles TIM6 global and DAC1 underrun error interrupts.
 */
void TIM6_DAC1_IRQHandler(void) {
	/* USER CODE BEGIN TIM6_DAC1_IRQn 0 */
	if (LL_TIM_IsActiveFlag_UPDATE(TIM6)) {
		updateDisplay();
	}
	/* USER CODE END TIM6_DAC1_IRQn 0 */

	/* USER CODE BEGIN TIM6_DAC1_IRQn 1 */
	LL_TIM_ClearFlag_UPDATE(TIM6);
	/* USER CODE END TIM6_DAC1_IRQn 1 */
}

/**
 * @brief This function handles TIM7 global and DAC2 underrun error interrupts.
 */
void TIM7_DAC2_IRQHandler(void) {
	/* USER CODE BEGIN TIM7_DAC2_IRQn 0 */
	if (LL_TIM_IsActiveFlag_UPDATE(TIM7)) {
		nextStringSequence = true;
	}
	/* USER CODE END TIM7_DAC2_IRQn 0 */

	/* USER CODE BEGIN TIM7_DAC2_IRQn 1 */
	LL_TIM_ClearFlag_UPDATE(TIM7);
	/* USER CODE END TIM7_DAC2_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
