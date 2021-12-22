/*
 * lps25hb.c
 *
 *  Created on: 16. 12. 2021
 *      Author: Michal
 */

#include "lps25hb.h"

uint8_t addresLPS25HB = LPS25HB_DEVICE_ADDRESS_0;

uint8_t lps25hb_read_byte(uint8_t reg_addr) {
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addresLPS25HB, 0));
}

void lps25hb_write_byte(uint8_t reg_addr, uint8_t value) {
	i2c_master_write(value, reg_addr, addresLPS25HB, 0);
}

void lps25hb_readArray(uint8_t *data, uint8_t reg, uint8_t length) {
	i2c_master_read(data, length, reg, addresLPS25HB, 1);
}
void lps25hb_get_pressure(float *pressure) {
	uint8_t buffer[3];
	uint32_t raw_press = 0;
	uint8_t i;
	lps25hb_readArray(buffer, LPS25HB_ADDRESS_PressOut_XL, 3);
	for (i = 0; i < 3; i++)
		raw_press |= (((uint32_t) buffer[i]) << (8 * i));
	if (raw_press & 0x00800000)
		raw_press |= 0xFF000000;
	*pressure = ((float) raw_press) / 4096;
}
void lps25hb_get_pressureOffset(float *pressureOffset) {
	uint8_t buffer[2];
	int16_t raw_press;
	lps25hb_readArray(buffer, LPS25HB_RPDS_L_REG, 2);
	raw_press = (int16_t)((((uint16_t)buffer[1]) << 8) + (uint16_t)buffer[0]);
	*pressureOffset =  ((float) raw_press) / 4096;
}
void lps25hb_get_pressureWithOffset(float *pressureWithOffset){
	float rawPressure = -1;
	float pressureOffset = -1;
	lps25hb_get_pressure(&rawPressure);
	lps25hb_get_pressureOffset(&pressureOffset);
	*pressureWithOffset = rawPressure + pressureOffset;
}
void lps25hb_get_altitude(float *altitude) {
	float pressure = 0;
	lps25hb_get_pressure(&pressure);
	float pressurePW = pow(pressure / LPS25HB_ALTITUDE_P0, LPS25HB_ALTITUDE_PW);
	*altitude = LPS25HB_ALTITUDE_CONST * (1 - pressurePW);
}
uint8_t lps25hb_init(void) {
	uint8_t result = 0;
	LL_mDelay(100);
	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
	if (val == LPS25HB_WHO_AM_I_VALUE) {
		result = 1;
	} else
	//if the device is not found on one address, try another one
	{
		addresLPS25HB = LPS25HB_DEVICE_ADDRESS_1;
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRES);
		if (val == LPS25HB_WHO_AM_I_VALUE)
			result = 1;
		else
			result = 0;
	}
	if (result == 1) {
		//load reserved bits from device
		uint8_t control1 = lps25hb_read_byte(LPS25HB_ADDRESS_CTRL1);
		//active mode
		control1 &= ~LPS25HB_PD_MASK;
		control1 |= ((uint8_t) 1) << LPS25HB_PD_BIT;
		//output registers not updated until MSB and LSB reading
		control1 &= ~LPS25HB_BDU_MASK;
		control1 |= ((uint8_t) 1) << LPS25HB_BDU_BIT;
		//ODR register sampling
		control1 &= ~LPS25HB_ODR_MASK;
		control1 |= ((uint8_t) 2) << LPS25HB_ODR_BIT;
		// Reset AZ (Self clear)
		val = control1;
		control1 &= ~LPS25HB_RESET_AZ_MASK;
		control1 |= ((uint8_t) 1) << LPS25HB_RESET_AZ_BIT;
		//Write config. to device
		lps25hb_write_byte(LPS25HB_ADDRESS_CTRL1, control1);
		control1 = val;
		val = lps25hb_read_byte(LPS25HB_ADDRESS_CTRL1);
		result = val == control1 ? 1 : 0;
	}
	return result;

}
