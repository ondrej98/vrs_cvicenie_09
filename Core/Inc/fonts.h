/*
 * font.h
 *
 *  Created on: Dec 1, 2021
 *      Author: Ondrej
 */

#ifndef INC_FONTS_H_
#define INC_FONTS_H_
#include "main.h"

#define FONTS_DIGITS_START 0
#define FONTS_CHARS_START 10
#define FONTS_UNDERSCORE 36

typedef enum{
	false = 0,
	true = 1
}bool;

typedef struct{
	bool sA;
	bool sB;
	bool sC;
	bool sD;
	bool sE;
	bool sF;
	bool sG;
	bool sDot;
}SegmentDigitStruct;



SegmentDigitStruct GetSegmentDigit(uint8_t chr);

#endif /* INC_FONTS_H_ */
