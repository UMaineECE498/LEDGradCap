
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

	while (1) {
		x[i] = accel_reg_read(ACCEL_X_AXIS) & 0x3F;	// Get X axis
		if (x[i] & 0x20) {
			x[i] = x[i] | 0xc0;
		}
		i++;
		i = i & 0x07;
		a = 0;
		for (j = 0; j < 8; j++) {	// Average
			a += x[j];
		}
		a = a / 8;
		if (a>20) {
			grad_cap_mode();
		}
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

		if (tilted_to_left()) {
			step = 0;
			loops = 0;
		}
		//@todo determine the best delay, sleep?
		_delay_ms(100);
	}
}

//detect a clap show a flash of Maine Blue

enum { RIGHT, CCW, LEFT, CWDISP, CWBLANK };

// This does not work
void do_shaky_shaky(void)
{
	uint8_t state = CCW;
	int8_t x;

	while (1) {
		x = accel_reg_read(ACCEL_X_AXIS) & 0x3F;	// Get X axis
		if (x > 31)
			x = x - 64;
		switch (state) {
			case CWDISP:	// Starting CW travel - display message once
				display_msg();
				state = CWBLANK;
				break;
			case CWBLANK:	// Message ended but still traveling CW
				if (x == 31)
					state = RIGHT;	// Wait until at right
				break;
			case CCW:	// Traveling CCW - no message
				if (x == -32)
					state = LEFT;	// Wait until at left
				break;
			case RIGHT:	// At right extreme
				if (x < 31)
					state = CCW;	// Wait until turn around
				break;
			case LEFT:	// At left extreme
				if (x > -32)
					state = CWDISP;	// Wait until turn around
				break;
		}
	}
	return;
}

const uint8_t msg[] PROGMEM={
				0x00,0x00,0x7f,
				0x00,0x00,0x02,
				0x00,0x00,0x04,
				0x00,0x00,0x02,
				0x00,0x00,0x7f,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x41,
				0x00,0x00,0x41,
				0x00,0x00,0x7f,
				0x00,0x00,0x41,
				0x00,0x00,0x41,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x7f,
				0x00,0x00,0x08,
				0x00,0x00,0x14,
				0x00,0x00,0x22,
				0x00,0x00,0x41,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x00,
				0x00,0x00,0x7f,
				0x00,0x00,0x49,
				0x00,0x00,0x49,
				0x00,0x00,0x49,
				0x00,0x00,0x41,
};
#define MSGLEN 87

void display_msg(void)
{
	unsigned char r, g, b, i, j;

	for (i=0;i<MSGLEN;i+=3) {
//		r=pgm_read_byte(&(msg[i]));
//		g=pgm_read_byte(&(msg[i+1]));
//		b=pgm_read_byte(&(msg[i+2]));
		r=0;
		g=0;
		b=0;
		if (i&0x01) b=0xaa;
		memset(red,255,8);
		memset(green,255,8);
		memset(blue,255,8);
		for (j = 0; j < 8; j++) {
			if ((r & 0x01) == 0) {
				red[j] = 0;
			}
			if ((g & 0x01) == 0) {
				green[j] = 0;
			}
			if ((b & 0x01) == 0) {
				blue[j] = 0;
			}
			r=r>>1;
			g=g>>1;
			b=b>>1;
		}
		send_leds(red, green, blue);	// Write
		_delay_us(10);
	}
	memset(red,0,8);
	memset(green,0,8);
	memset(blue,0,8);
	send_leds(red, green, blue);	// Write
	return;
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
