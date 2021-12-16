/*
 * hts221.c
 *
 *  Created on: 15. 12. 2021
 *      Author: Ondrej
 */

#include "../Core/Inc/main.h"
#include "../Core/Inc/i2c.h"

#define HTS221_DEVICE_ADDRESS		0xBE

#define HTS221_WHO_AM_I_VALUE		0xBC
#define HTS221_WHO_AM_I_ADDRES		0x0F

#define HTS221_ADDRESS_CTRL1		0x20

#define HTS221_ADDRESS_H_OUT_L		0x28
#define HTS221_ADDRESS_H_OUT_H		0x29
#define HTS221_ADDRESS_T_OUT_L		0x2A
#define HTS221_ADDRESS_T_OUT_H		0x2B

#define	HTS221_ADDRESS_H0_rH_x2_L 	0x30
#define	HTS221_ADDRESS_H1_rH_x2_H	0x31
#define	HTS221_ADDRESS_T0_degC_x8	0x32
#define	HTS221_ADDRESS_T1_degC_x8	0x33

#define HTS221_ADDRESS_T1_T0_MSB	0x35
#define	HTS221_ADDRESS_H0_OUT_L		0x36
#define	HTS221_ADDRESS_H0_OUT_H		0x37

#define	HTS221_ADDRESS_H1_OUT_L		0x3A
#define	HTS221_ADDRESS_H1_OUT_H		0x3B
#define	HTS221_ADDRESS_T0_OUT_L		0x3C
#define	HTS221_ADDRESS_T0_OUT_H		0x3D
#define	HTS221_ADDRESS_T1_OUT_L		0x3E
#define	HTS221_ADDRESS_T1_OUT_H		0x3F

#define HTS221_PD_BIT 		(uint8_t)7
#define HTS221_BDU_BIT		(uint8_t)2

#define HTS221_PD_MASK		(uint8_t)0x80
#define HTS221_BDU_MASK		(uint8_t)0x04

uint8_t hts221_init(void);
//void hts221_get_acc(float *x, float *y, float *z);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
//int8_t hts221_get_temp();