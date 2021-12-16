/*
 * hts221.c
 *
 *  Created on: 15. 12. 2021
 *      Author: Ondrej
 */

#include "hts221.h"

uint8_t addresHTS221 = HTS221_DEVICE_ADDRESS;

uint8_t hts221_read_byte(uint8_t reg_addr) {
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addresHTS221, 0));
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value) {
	i2c_master_write(value, reg_addr, addresHTS221, 0);
}

void hts221_readArray(uint8_t *data, uint8_t reg, uint8_t length) {
	i2c_master_read(data, length, reg, addresHTS221, 1);
}

uint8_t hts221_init(void) {
	uint8_t status = 0;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);

	if (val == HTS221_WHO_AM_I_VALUE) {
		status = 1;
		//load reserved bits from device
		uint8_t control1 = hts221_read_byte(HTS221_ADDRESS_CTRL1);
		//active mode
		control1 &= ~HTS221_PD_MASK;
		control1 |= ((uint8_t) 1) << HTS221_PD_BIT;
		//output registers not updated until MSB and LSB reading
		control1 &= ~HTS221_BDU_MASK;
		control1 |= ((uint8_t) 1) << HTS221_BDU_BIT;
		//Write config. to device
		/*hts221_write_byte(HTS221_ADDRESS_CTRL1, control1);
		val = hts221_read_byte(HTS221_ADDRESS_CTRL1);
		status = val == control1 ? 1 : 0;*/
	}
	return status;
}
