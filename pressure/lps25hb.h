/*
 * lps25hb.h
 *
 *  Created on: 16. 12. 2021
 *      Author: Michal
 */


#include "../Core/Inc/main.h"
#include "../Core/Inc/i2c.h"


#define LPS25HB_DEVICE_ADDRESS_0	0xB8
#define LPS25HB_DEVICE_ADDRESS_1	0xBA

#define LPS25HB_WHO_AM_I_VALUE		0xBD
#define LPS25HB_WHO_AM_I_ADDRES		0x0F

#define LPS25HB_ADDRESS_CTRL1		0x20
#define LPS25HB_ADDRESS_PressOut_XL	0x28
#define LPS25HB_ADDRESS_PressOut_L	0x29
#define LPS25HB_ADDRESS_PressOut_H	0x2A


#define LPS25HB_PD_BIT 		(uint8_t)7
#define LPS25HB_BDU_BIT		(uint8_t)2
#define LPS25HB_ODR_BIT     (uint8_t)4

#define LPS25HB_PD_MASK		(uint8_t)0x80
#define LPS25HB_BDU_MASK	(uint8_t)0x04
#define LPS25HB_ODR_MASK    (uint8_t)0x70

uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);

