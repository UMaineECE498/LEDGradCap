#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "i2cmaster.h"
#include "accel.h"

// Read from the specified register within the accelerometer
uint8_t accel_reg_read(uint8_t addr)
{
	uint8_t value;

	// Configure I2C Transaction

	// Left shift ADDR 1 bit.  I2c addresses are 7 bits, lsb sets mode
	i2c_start((MMA7660_ADR << 1) + I2C_WRITE);		// Start in write mode
	i2c_write(addr);								// Read from specified address

	i2c_rep_start((MMA7660_ADR << 1) + I2C_READ);	// Alert read mode
	value = i2c_readNak();							// Get the actual value
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

ORIENTATION_T accel_get_orientation(void)
{
	int8_t threshold = 10;

	int8_t average = axis_average(ACCEL_X_AXIS);

	// Start with X Axis (Right/Left)
	if (average > threshold)
	{
		return accel_confirm_orientation(ORIENT_L, threshold);
	} 
	else if (average < threshold * -1)
	{
		return accel_confirm_orientation(ORIENT_R, threshold * -1);
	}

	// Try Y axis (F/B)
	average = axis_average(ACCEL_Y_AXIS);	
	if (average > threshold)
	{
		return accel_confirm_orientation(ORIENT_F, threshold);
	} 
	else if (average < threshold * -1) 
	{
		return accel_confirm_orientation(ORIENT_B, threshold * -1);
	}

	return ORIENT_UK;		// Orientation not clear
}

ORIENTATION_T accel_confirm_orientation(ORIENTATION_T orientation, int8_t threshold)
{
	uint8_t i=0;
	int8_t x=0, y=0;

	for (i = 0; i < 8; i++)
	{
		_delay_ms(50);
		x = axis_average(ACCEL_X_AXIS);
		y = axis_average(ACCEL_Y_AXIS);

		if (orientation == ORIENT_L || orientation == ORIENT_R)
		{
			if (-threshold < x && x < threshold)
			{
				return ORIENT_UK;
			}
		}
		else if (orientation == ORIENT_F || orientation == ORIENT_B)
		{
			if (-threshold < y && y < threshold)
			{
				return ORIENT_UK;
			}
		}
	}

	return orientation;
}
