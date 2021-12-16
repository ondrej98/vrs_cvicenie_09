/*
 * fonts.c
 *
 *  Created on: Dec 1, 2021
 *      Author: Ondrej
 */
#include "fonts.h"


const uint8_t ConverterValue_SegmentA = 0b01000000;
const uint8_t ConverterValue_SegmentB = 0b00100000;
const uint8_t ConverterValue_SegmentC = 0b00010000;
const uint8_t ConverterValue_SegmentD = 0b00001000;
const uint8_t ConverterValue_SegmentE = 0b00000100;
const uint8_t ConverterValue_SegmentF = 0b00000010;
const uint8_t ConverterValue_SegmentG = 0b00000001;
const uint8_t ConverterValue_SegmentDot = 0b10000000;
//
//  Font data for Courier New 12pt
//
const uint8_t Font_Table[] = {
// 1 row = abcdefg(dt) [0b00000000]
		//Expects 10(digits) + 24(chars) + 1(_)
		0x7E,// 0
		0x30, // 1
		0x6D, // 2
		0x79, // 3
		0x33, // 4
		0x5B, // 5
		0x5F, // 6
		0x70, // 7
		0x7F, // 8
		0x7B, // 9
		0x77, // A
		0x1F, // b
		0x4E, // C
		0x3D, // d
		0x4F, // E
		0x47, // F
		0x5E, // G
		0x37, // H
		0x06, // I
		0x3C, // J
		0x57, // K*
		0x0E, // L
		0x6A, // M*
		0x15, // N
		0x1D, // o
		0x67, // P
		0x73, // Q
		0x05, // R
		0x5B, // S
		0x0F, // T
		0x3E, // U
		0x2A, // V*
		0x3F, // W*
		0x49, // X*
		0x3B, // Y
		0x6D, // Z*
		0x08, // _
		0x01, //-
		0x80, //.,
		};

SegmentDigitStruct GetSegmentDigit(uint8_t chr) {
	SegmentDigitStruct result;
	if ((chr >= '0' && chr <= '9') || (chr >= 'A' && chr <= 'Z')
			|| chr == '_') {
		uint8_t fontChar = 0;
		uint8_t index = 0;
		if (chr >= '0' && chr <= '9') {
			index = chr - '0';
			fontChar = Font_Table[FONTS_DIGITS_START + index];
		} else if (chr >= 'A' && chr <= 'Z') {
			index = chr - 'A';
			fontChar = Font_Table[FONTS_CHARS_START + index];
		} else if (chr == '_') {
			fontChar = Font_Table[FONTS_UNDERSCORE];
		}else if(chr == '-'){
			fontChar = Font_Table[FONTS_MINUS];
		}else if(chr == '.' || chr == ','){
			fontChar = Font_Table[FONTS_DOT];
		}
		result.sA = fontChar & ConverterValue_SegmentA ? true : false;
		result.sB = fontChar & ConverterValue_SegmentB ? true : false;
		result.sC = fontChar & ConverterValue_SegmentC ? true : false;
		result.sD = fontChar & ConverterValue_SegmentD ? true : false;
		result.sE = fontChar & ConverterValue_SegmentE ? true : false;
		result.sF = fontChar & ConverterValue_SegmentF ? true : false;
		result.sG = fontChar & ConverterValue_SegmentG ? true : false;
		result.sDot = fontChar & ConverterValue_SegmentDot ? true : false;
	}
	else{
		result.sA = true;
		result.sB = true;
		result.sC = true;
		result.sD = true;
		result.sE = true;
		result.sF = true;
		result.sG = true;
		result.sDot = true;
	}
	return result;
}
