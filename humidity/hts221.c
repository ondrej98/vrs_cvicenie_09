/*
 * hts221.c
 *
 *  Created on: 15. 12. 2021
 *      Author: Ondrej
 */

#include "hts221.h"

uint8_t addresHTS221 = HTS221_DEVICE_ADDRESS;
Hts221HumidityStruct HumidityFactoryCoef;
Hts221TemperatureStruct TemperatureFactoryCoef;

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
	uint8_t result = 0;
	LL_mDelay(100);
	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);
	if (val == HTS221_WHO_AM_I_VALUE) {
		result = 1;
		//load reserved bits from device
		uint8_t control1 = hts221_read_byte(HTS221_ADDRESS_CTRL1);
		//active mode
		control1 &= ~HTS221_PD_MASK;
		control1 |= ((uint8_t) 1) << HTS221_PD_BIT;
		//output registers not updated until MSB and LSB reading
		control1 &= ~HTS221_BDU_MASK;
		control1 |= ((uint8_t) 1) << HTS221_BDU_BIT;

		control1 &= ~HTS221_ODR_MASK;
		control1 |= ((uint8_t) 2) << HTS221_ODR_BIT;
		//Write config. to device
		hts221_write_byte(HTS221_ADDRESS_CTRL1, control1);
		val = hts221_read_byte(HTS221_ADDRESS_CTRL1);
		result = val == control1 ? 1 : 0;
		hts221_get_factory_coef(&HumidityFactoryCoef, &TemperatureFactoryCoef);
	}
	return result;
}

void hts221_get_humidity(float *humidity) {
	uint8_t buffer[2] = { 0 };
	hts221_readArray(buffer, HTS221_ADDRESS_H_OUT_L, 2);
	int16_t hOut = ((int16_t) buffer[1]) << 8 | buffer[0];
	int16_t h0Rh = HumidityFactoryCoef.h0Rh;
	int16_t h1Rh = HumidityFactoryCoef.h1Rh;
	int16_t h0T0 = HumidityFactoryCoef.h0Out;
	int16_t h1T0 = HumidityFactoryCoef.h1Out;
	*humidity = ((float)(h1Rh - h0Rh) * (float)(hOut - h0T0)) / (float)(h1T0 - h0T0) + h0Rh;
}

void hts221_get_temperature(float *temperature) {
	uint8_t buffer[2] = { 0 };
	//hts221_readArray(buffer, HTS221_ADDRESS_T_OUT_L, 2);
	buffer[0] = hts221_read_byte(HTS221_ADDRESS_T_OUT_L);
	buffer[1] = hts221_read_byte(HTS221_ADDRESS_T_OUT_H);
	int16_t tOut = ((int16_t) buffer[1]) << 8 | buffer[0];
	int16_t t0Deg = TemperatureFactoryCoef.t0DegC;
	int16_t t1Deg = TemperatureFactoryCoef.t1DegC;
	int16_t t0Out = TemperatureFactoryCoef.t0Out;
	int16_t t1Out = TemperatureFactoryCoef.t1Out;
	*temperature = ((float)(t1Deg - t0Deg) * (float)(tOut - t0Out)) / (float)(t1Out - t0Out) + t0Deg;
}

void hts221_get_factory_coef(Hts221HumidityStruct *humidityStruct,
		Hts221TemperatureStruct *temperatureStruct) {
	//Get humidity factory coef.
	int16_t h0RhX2 = (int16_t)hts221_read_byte(HTS221_ADDRESS_H0_rH_x2);
	int16_t h1RhX2 = (int16_t)hts221_read_byte(HTS221_ADDRESS_H1_rH_x2);
	uint8_t buffer[4] = { 0 };
	hts221_readArray(buffer, HTS221_ADDRESS_H0_OUT_L, 2);
	hts221_readArray(buffer + 2, HTS221_ADDRESS_H1_OUT_L, 2);
	int16_t h0Out = ((int16_t) buffer[1]) << 8 | (int16_t)buffer[0];
	int16_t h1Out = ((int16_t) buffer[3]) << 8 | (int16_t)buffer[2];

	humidityStruct->h0Rh = h0RhX2 >> 1;
	humidityStruct->h1Rh = h1RhX2 >> 1;
	humidityStruct->h0Out = h0Out;
	humidityStruct->h1Out = h1Out;
	//Get temperature factory coef.
	buffer[0] = hts221_read_byte(HTS221_ADDRESS_T0_degC_x8);
	buffer[2] = hts221_read_byte(HTS221_ADDRESS_T1_degC_x8);
	int16_t t0t1Msb = (int16_t)hts221_read_byte(HTS221_ADDRESS_T1_T0_MSB);
	buffer[1] = t0t1Msb & 0x03;
	buffer[3] = t0t1Msb & 0x0C;
	int16_t t0DegX8 = ((int16_t) buffer[1]) << 8 | (int16_t)buffer[0];
	int16_t t1DegX8 = ((int16_t) buffer[3]) << 6 | (int16_t)buffer[2];
	hts221_readArray(buffer, HTS221_ADDRESS_T0_OUT_L, 4);
	//hts221_readArray(buffer + 2, HTS221_ADDRESS_T1_OUT_L, 2);
	int16_t t0Out = ((int16_t) buffer[1]) << 8 | (int16_t)buffer[0];
	int16_t t1Out = ((int16_t) buffer[3]) << 8 | (int16_t)buffer[2];

	temperatureStruct->t0DegC = t0DegX8 >> 3;
	temperatureStruct->t1DegC = t1DegX8 >> 3;
	temperatureStruct->t0Out = t0Out;
	temperatureStruct->t1Out = t1Out;
}
