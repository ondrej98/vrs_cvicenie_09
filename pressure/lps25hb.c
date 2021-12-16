/*
 * lps25hb.c
 *
 *  Created on: 16. 12. 2021
 *      Author: Michal
 */

#include "lps25hb.h"


uint8_t addres = LPS25HB_DEVICE_ADDRESS_0;

uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres, 0));
}


void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres, 0);
}


void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres, 1);
}


uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = lsm6ds0_read_byte(LSM6DS0_WHO_AM_I_ADDRES);

	if(val == LSM6DS0_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres = LSM6DS0_DEVICE_ADDRESS_1;
		val = lsm6ds0_read_byte(LSM6DS0_WHO_AM_I_ADDRES);
		if(val == LSM6DS0_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			//return status;
		}
	}

	//acc device init

	uint8_t ctrl1 = 8 << 4; // +-2g res
	lps25hb_write_byte(LSM6DS0_ADDRESS_CTRL1, ctrl1);

	return status;
}
