/*
 * display.h
 *
 *  Created on: 7. 12. 2021
 *      Author: Ondrej
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_
//#include "fonts.h"
#include "fonts.h"

#define SEGMENT_A_ON		LL_GPIO_ResetOutputPin(S_A_GPIO_Port, S_A_Pin)
#define SEGMENT_B_ON		LL_GPIO_ResetOutputPin(S_B_GPIO_Port, S_B_Pin)
#define SEGMENT_C_ON		LL_GPIO_ResetOutputPin(S_C_GPIO_Port, S_C_Pin)
#define SEGMENT_D_ON		LL_GPIO_ResetOutputPin(S_D_GPIO_Port, S_D_Pin)
#define SEGMENT_E_ON		LL_GPIO_ResetOutputPin(S_E_GPIO_Port, S_E_Pin)
#define SEGMENT_F_ON		LL_GPIO_ResetOutputPin(S_F_GPIO_Port, S_F_Pin)
#define SEGMENT_G_ON		LL_GPIO_ResetOutputPin(S_G_GPIO_Port, S_G_Pin)
#define SEGMENT_DP_ON		LL_GPIO_ResetOutputPin(S_DP_GPIO_Port, S_DP_Pin)

#define SEGMENT_A_OFF		LL_GPIO_SetOutputPin(S_A_GPIO_Port, S_A_Pin)
#define SEGMENT_B_OFF		LL_GPIO_SetOutputPin(S_B_GPIO_Port, S_B_Pin)
#define SEGMENT_C_OFF		LL_GPIO_SetOutputPin(S_C_GPIO_Port, S_C_Pin)
#define SEGMENT_D_OFF		LL_GPIO_SetOutputPin(S_D_GPIO_Port, S_D_Pin)
#define SEGMENT_E_OFF		LL_GPIO_SetOutputPin(S_E_GPIO_Port, S_E_Pin)
#define SEGMENT_F_OFF		LL_GPIO_SetOutputPin(S_F_GPIO_Port, S_F_Pin)
#define SEGMENT_G_OFF		LL_GPIO_SetOutputPin(S_G_GPIO_Port, S_G_Pin)
#define SEGMENT_DP_OFF		LL_GPIO_SetOutputPin(S_DP_GPIO_Port, S_DP_Pin)

#define DIGIT_0_ON		LL_GPIO_SetOutputPin(D_0_GPIO_Port, D_0_Pin)
#define DIGIT_1_ON		LL_GPIO_SetOutputPin(D_1_GPIO_Port, D_1_Pin)
#define DIGIT_2_ON		LL_GPIO_SetOutputPin(D_2_GPIO_Port, D_2_Pin)
#define DIGIT_3_ON		LL_GPIO_SetOutputPin(D_3_GPIO_Port, D_3_Pin)
#define DIGIT_TIME_ON	LL_GPIO_SetOutputPin(D_T_GPIO_Port, D_T_Pin)
#define DIGIT_0_OFF		LL_GPIO_ResetOutputPin(D_0_GPIO_Port, D_0_Pin)
#define DIGIT_1_OFF		LL_GPIO_ResetOutputPin(D_1_GPIO_Port, D_1_Pin)
#define DIGIT_2_OFF		LL_GPIO_ResetOutputPin(D_2_GPIO_Port, D_2_Pin)
#define DIGIT_3_OFF		LL_GPIO_ResetOutputPin(D_3_GPIO_Port, D_3_Pin)
#define DIGIT_TIME_OFF	LL_GPIO_ResetOutputPin(D_T_GPIO_Port, D_T_Pin)

typedef struct {
	uint8_t index;
	uint8_t chr;
} DisplayDigitData_;

/* Reset (turn-off) all digits*/
void resetDigits(void);
/* Reset (turn-on) all digits*/
void setDigits(void);
/*Reset (turn-off) all the segments of display*/
void resetSegments(void);
/*Set (turn-on) all the segments of display*/
void setSegments(void);
/*Set specified segments of display on*/
void segmentsOn(uint8_t index, SegmentDigitStruct digitStruct);
/*Display provided char on the specified digit*/
void displayCharOnDigit(DisplayDigitData_ digitData);
DisplayDigitData_ DisplayDigit_0;
DisplayDigitData_ DisplayDigit_1;
DisplayDigitData_ DisplayDigit_2;
DisplayDigitData_ DisplayDigit_3;

void updateDisplay(void);
#endif /* INC_DISPLAY_H_ */
