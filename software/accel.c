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

	i2c_write(addr); 		// Set to read from x axis register
	i2c_rep_start((MMA7660_ADR << 1) + I2C_READ);
	value=i2c_readNak();
	i2c_stop();
	return value;
}
