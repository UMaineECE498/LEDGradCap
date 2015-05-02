
#define F_CPU 8000000UL
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
			red[1] = 100;
		} else {
			red[1] = 0;
		}

		send_leds(red, green, blue);

		// if (a>20) {
		// 	grad_cap_mode();
		// }
	}
	return 0;
}




// if Z~=1G I'm Flat
// if Z~=0 I'm Shaky Shaky
int grad_cap_mode(void)
{
	uint8_t z = 0;

	while (1) {
		z = accel_reg_read(ACCEL_Z_AXIS) & 0x3F;
		if (z > 16) {
			return 1;
		}

	}

	return 0;
}

void do_grad_cap(void)
{
	int step = 0;
	int loops = 0;

	while (grad_cap_mode()) {
		if (loops < NUM_LOOPS) {
			//change_leds(step);
		}
		step++;
		if (step > MAX_STEPS) {
			step = 0;
			loops++;
		}

		if (accel_reg_read(ACCEL_X_AXIS) & 0x3F) {
			step = 0;
			loops = 0;
		}
		//@todo determine the best delay, sleep?
		_delay_ms(100);
	}
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
