/*
 * display.c
 *
 *  Created on: 7. 12. 2021
 *      Author: Ondrej
 */

#include "display.h"

extern DisplayDigitData_ DisplayDigit_0;
extern DisplayDigitData_ DisplayDigit_1;
extern DisplayDigitData_ DisplayDigit_2;
extern DisplayDigitData_ DisplayDigit_3;
static uint8_t indexer = 0;
void resetSegments(void) {
	SEGMENT_A_OFF;
	SEGMENT_B_OFF;
	SEGMENT_C_OFF;
	SEGMENT_D_OFF;
	SEGMENT_E_OFF;
	SEGMENT_F_OFF;
	SEGMENT_G_OFF;
	SEGMENT_DP_OFF;
}

void setSegments(void) {
	SEGMENT_A_ON;
	SEGMENT_B_ON;
	SEGMENT_C_ON;
	SEGMENT_D_ON;
	SEGMENT_E_ON;
	SEGMENT_F_ON;
	SEGMENT_G_ON;
	SEGMENT_DP_ON;
}

void resetDigits(void) {
	DIGIT_0_OFF;
	DIGIT_1_OFF;
	DIGIT_2_OFF;
	DIGIT_3_OFF;
	DIGIT_TIME_OFF;
}

void setDigits(void) {
	DIGIT_0_ON;
	DIGIT_1_ON;
	DIGIT_2_ON;
	DIGIT_3_ON;
	DIGIT_TIME_ON;
}

void segmentsOn(uint8_t index, SegmentDigitStruct digitStruct) {
//	resetSegments();
	if (digitStruct.sA)
		SEGMENT_A_ON;
	else SEGMENT_A_OFF;
	if (digitStruct.sB)
		SEGMENT_B_ON;
	else SEGMENT_B_OFF;
	if (digitStruct.sC)
		SEGMENT_C_ON;
	else SEGMENT_C_OFF;
	if (digitStruct.sD)
		SEGMENT_D_ON;
	else SEGMENT_D_OFF;
	if (digitStruct.sE)
		SEGMENT_E_ON;
	else SEGMENT_E_OFF;
	if (digitStruct.sF)
		SEGMENT_F_ON;
	else SEGMENT_F_OFF;
	if (digitStruct.sG)
		SEGMENT_G_ON;
	else SEGMENT_G_OFF;
	if (digitStruct.sDot)
		SEGMENT_DP_ON;
	else SEGMENT_DP_OFF;

	resetDigits();
	if (index == 0)
		DIGIT_0_ON;
	else if (index == 1)
		DIGIT_1_ON;
	else if (index == 2)
		DIGIT_2_ON;
	else if (index == 3)
		DIGIT_3_ON;
}

void displayCharOnDigit(DisplayDigitData_ digitData) {
	SegmentDigitStruct digitStruct = GetSegmentDigit(digitData.chr);
	segmentsOn(digitData.index, digitStruct);
}
void updateDisplay(void) {

	switch (indexer) {
	default:
		resetDigits();
		resetSegments();
		indexer = 0;
		break;
	case 0:
		displayCharOnDigit(DisplayDigit_0);
		indexer++;
		break;
	case 1:
		displayCharOnDigit(DisplayDigit_1);
		indexer++;
		break;
	case 2:
		displayCharOnDigit(DisplayDigit_2);
		indexer++;
		break;
	case 3:
		displayCharOnDigit(DisplayDigit_3);
		indexer++;
		break;

	}
}
