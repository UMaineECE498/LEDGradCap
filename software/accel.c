#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "i2cmaster.h"
#include "accel.h"

// Read from the specified register within the accelerometer
uint8_t accel_reg_read(uint8_t addr)
{
	uint8_t value;

	i2c_start((MMA7660_ADR << 1) + I2C_WRITE);
	i2c_write(addr);	// Set to read from x axis register
	i2c_rep_start((MMA7660_ADR << 1) + I2C_READ);
	value = i2c_readNak();
	i2c_stop();
	return value;
}

// For the given axis, calculate an average
int8_t axis_average(uint8_t axis)
{
	uint8_t i, v;	// Counter, temp variable for raw Accel value
	int16_t a=0;	// Average

	for (i=0;i<8;i++) {		// 8 time
		v=accel_reg_read(axis)&0x3F;	// Get X axis
		if (v&0x20) {		// Sign extend
			v=v|0xc0;
		}
		a+=v;				// Sum
	}
	a=a/8;					// Average
	return a;
}
