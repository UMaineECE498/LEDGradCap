
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <avr/pgmspace.h>


#include "system.h"
#include "i2cmaster.h"
#include "led.h"
#include "accel.h"
#include "ledRoutines.h"



int grad_cap_mode(void);
void do_grad_cap(void);
void do_shaky_shaky(void);
uint8_t tilted_to_left(void);
// Initialize the system
void system_init(void);
void display_msg(void);


#define NUM_LOOPS 10		//number of loops
#define MAX_STEPS 5		//

uint8_t red[8] = { 0 };	// Red values
uint8_t green[8] = { 0 };	// Green values
uint8_t blue[8] = { 0 };	// Blue values

int main(void)
{
	int8_t x[8];		// X axis accel values
	uint8_t i = 0;		// X axis index
	uint8_t j = 0;		// General index
	int16_t a = 0;		// Average value

	system_init();		// System init
	send_leds(red, green, blue);	// Write

	while (1) {
		if (accel_get_orientation() == ORIENT_L)
		{
			myfade();
		} else {
			memset(red,0,8);
			memset(green,0,8);
			memset(blue,0,8);
		}

		send_leds(red, green, blue);

	}
	return 0;
}

// Initiailize the system
void system_init(void)
{
	// Remove System Clock Division
	CCP = 0xD8;
	CLKPSR = 0x00;

	// Enable LED Output Pins
	LED_DATA_PORT &= ~_BV(LED_DATA_PIN);	// Set output to zero first
	LED_DATA_DIR |= _BV(LED_DATA_PIN);	// LED TX line - need to be an output

	// Enable LED Output MOSFET
	LED_EN_PORT &= ~_BV(LED_EN_PIN);
	LED_EN_DIR |= _BV(LED_EN_PIN);
	LED_EN_PORT |= _BV(LED_EN_PIN);

	// Initialize bit-bang i2c and activate accelerometer
	i2c_init();

	i2c_start_wait((MMA7660_ADR << 1) + I2C_WRITE);
	i2c_write(0x07);	// Set Device in active Mode
	i2c_write(0x01);	// Write active mode bit
	i2c_stop();

	return;
}
